// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cPlanetTransformator.h"
#include "../engine/cEngine.h"
#include "CommonExternal.h"

namespace Forradia {

float cPlanetTransformator::GetNewY(float Y, float TileX, float TileY) {
  auto Result = Y;
  auto DX = (int)TileX - Engine.Player.Position.X;
  auto DY = (int)TileY - Engine.Player.Position.Y;
  auto Distance = DX * DX + DY * DY;

  Result -= Distance * 0.01f;

  return Result;
}

} // namespace Forradia
