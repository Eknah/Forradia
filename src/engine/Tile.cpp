// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Tile.h"
#include "../engine/IEngine.h"


namespace Forradia
{

    bool Tile::HasObjectWithFlag(ObjectFlags flag)
    {
        for (auto& Object : objects)
        {
            if (e.objectsContent.objectDescribers.count(Object->objectType))
            {
                auto objFlags = e.objectsContent.objectDescribers.at(Object->objectType).flags;

                if (objFlags & flag)
                    return true;
            }
        }

        return false;
    }

    bool Tile::HasObjectOfType(std::string objectName)
    {
        for (auto& Object : objects)
            if (Object->objectType == GetId(objectName))
                return true;

        return false;
    }

}  // namespace Forradia
