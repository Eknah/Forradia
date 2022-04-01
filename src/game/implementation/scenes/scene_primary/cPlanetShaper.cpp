// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cPlanetShaper.h"
#include "../engine/cEngine.h"
#include "implementation/functionality/actor/modules/cModuleMovementData.h"

namespace Forradia {

float cPlanetShaper::GetNewY(float Y, float TileX, float TileY) {
  auto Result = Y;
  auto DX = static_cast<int>(TileX) - Engine.GetPlayer().GetModule<cModuleMovementData>().Position.X;
  auto DY = static_cast<int>(TileY) - Engine.GetPlayer().GetModule<cModuleMovementData>().Position.Y;
  auto Distance = DX * DX + DY * DY;

  Result -= Distance * 0.01f;

  return Result;
}

}  // namespace Forradia
