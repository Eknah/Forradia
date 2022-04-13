// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ObjectsBehaviour.h"
#include "../engine/Aliases.h"
#include "ObjectDescriber.h"
#include "../engine/ObjectFlags.h"

namespace Forradia
{

    void ObjectsBehaviour::Add(String objectName, ObjectDescriber describer)
    {
        objectDescribers.insert({ GetId(objectName), describer });
    }

    void ObjectsBehaviour::Add(String objectName, char flags)
    {
        objectDescribers.insert({ GetId(objectName), ObjectDescriber(flags) });
    }

    void ObjectsBehaviour::AddMany(List<Tuple<String, char>> describers)
    {
        for (auto& desc : describers)
        {
            auto objectName = std::get<0>(desc);
            auto flags = std::get<1>(desc);

            objectDescribers.insert({ GetId(objectName), ObjectDescriber(flags) });
        }
    }

    void ObjectsBehaviour::SetOpacity(String objectName, float opacity)
    {
        objectDescribers.at(GetId(objectName)).opacity = opacity;
    }

    bool ObjectsBehaviour::IsMovable(int objectType) const
    {
        if (objectDescribers.count(objectType))
            return objectDescribers.at(objectType).flags & FlagMovable;

        return false;
    }

    bool ObjectsBehaviour::BlocksMovement(int objectType) const
    {
        if (objectDescribers.count(objectType))
            return objectDescribers.at(objectType).flags & FlagObstacle;

        return false;
    }

}  // namespace Forradia
