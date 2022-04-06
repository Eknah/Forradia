// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cTile.h"
#include "../engine/iEngine.h"


namespace Forradia {

bool cTile::HasObjectWithFlag(eObjectFlags Flag) {
    for (auto &Object : objects) {
        if (engine.objectsContent.objectDescriptions.count(Object->objectType)) {
            auto objFlags = engine.objectsContent.objectDescriptions.at(Object->objectType).flags;

            if (objFlags & Flag)
                return true;
        }
    }

    return false;
}

bool cTile::HasObjectOfType(std::string ObjectName) {
  for (auto &Object : objects)
    if (Object->objectType == GetId(ObjectName))
      return true;

  return false;
}

}  // namespace Forradia
