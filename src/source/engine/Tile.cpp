// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Tile.h"
#include "IEngine.h"


namespace Forradia
{
    bool Tile::HasObjectWithFlag(ObjectFlags flag)
    {
        for (auto& Object : objects)
        {
            if (e.objectsContent.objDescribers.count(Object->objectType))
            {
                auto objFlags = e.objectsContent.objDescribers.at(Object->objectType).flags;

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
}