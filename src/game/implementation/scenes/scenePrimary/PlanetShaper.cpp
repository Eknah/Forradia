// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "PlanetShaper.h"
#include "../engine/Engine.h"
#include "implementation/functionality/actor/modules/ModuleMovementData.h"

namespace Forradia {

float cPlanetShaper::GetNewY(float Y, float TileX, float TileY) {
    return Y;
  auto Result = Y;
  auto DX = static_cast<int>(TileX) - engine.GetPlayer().GetModule<cModuleMovementData>().position.x;
  auto DY = static_cast<int>(TileY) - engine.GetPlayer().GetModule<cModuleMovementData>().position.y;
  auto Distance = DX * DX + DY * DY;

  Result -= Distance * 0.01f;

  return Result;
}

}  // namespace Forradia
