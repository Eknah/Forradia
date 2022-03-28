// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cTile.h"
#include "../engine/iEngine.h"
#include "CommonExternal.h"

namespace Forradia {

bool cTile::MovementBlocked() {
  if (GroundType == GetId("GroundtypeWater"))
    return true;

  for (auto &Object : Objects)
    if (Engine.ObjectsContent.BlocksMovement(Object->ObjectType))
      return true;

  return false;
}

bool cTile::HasObjectOfType(std::string ObjectName) {
  for (auto &Object : Objects)
    if (Object->ObjectType == GetId(ObjectName))
      return true;

  return false;
}

}  // namespace Forradia
