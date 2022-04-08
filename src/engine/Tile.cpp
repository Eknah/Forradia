// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Tile.h"
#include "../engine/iEngine.h"


namespace Forradia {

bool cTile::HasObjectWithFlag(eObjectFlags flag) {
    for (auto &Object : objects) {
        if (engine.objectsContent.objectDescriptions.count(Object->objectType)) {
            auto objFlags = engine.objectsContent.objectDescriptions.at(Object->objectType).flags;

            if (objFlags & flag)
                return true;
        }
    }

    return false;
}

bool cTile::HasObjectOfType(std::string objectName) {
  for (auto &Object : objects)
    if (Object->objectType == GetId(objectName))
      return true;

  return false;
}

}  // namespace Forradia
