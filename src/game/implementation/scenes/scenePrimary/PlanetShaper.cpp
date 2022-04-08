// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "PlanetShaper.h"
#include "../engine/Engine.h"
#include "implementation/functionality/actor/modules/ModuleMovementData.h"

namespace Forradia {

float PlanetShaper::GetNewY(float y, float tileX, float tileY) {
    return y;
  auto result = y;
  auto dx = static_cast<int>(tileX) - engine.GetPlayer().GetModule<ModuleMovementData>().position.x;
  auto dy = static_cast<int>(tileY) - engine.GetPlayer().GetModule<ModuleMovementData>().position.y;
  auto distance = dx * dx + dy * dy;

  result -= distance * 0.01f;

  return result;
}

}  // namespace Forradia
