// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ObjectsBehaviour.h"
#include "Aliases.h"
#include "ObjectDescriber.h"
#include "ObjectFlags.h"

namespace Forradia
{

    void ObjectsBehaviour::Add(String objectName, ObjectDescriber describer)
    {
        objDescribers.insert({ GetId(objectName), describer });
    }

    void ObjectsBehaviour::Add(String objectName, char flags)
    {
        objDescribers.insert({ GetId(objectName), ObjectDescriber(flags) });
    }

    void ObjectsBehaviour::AddMany(List<Tuple<String, char>> describers)
    {
        for (auto& desc : describers)
        {
            auto objectName = std::get<0>(desc);
            auto flags = std::get<1>(desc);

            objDescribers.insert({ GetId(objectName), ObjectDescriber(flags) });
        }
    }

    void ObjectsBehaviour::SetOpacity(String objectName, float opacity)
    {
        objDescribers.at(GetId(objectName)).opacity = opacity;
    }

    bool ObjectsBehaviour::Movable(int objectType) const
    {
        if (objDescribers.count(objectType))
            return objDescribers.at(objectType).flags & FlagMovable;

        return false;
    }

    bool ObjectsBehaviour::BlocksMovement(int objectType) const
    {
        if (objDescribers.count(objectType))
            return objDescribers.at(objectType).flags & FlagObstacle;

        return false;
    }

}  // namespace Forradia
