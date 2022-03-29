// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cEngine.h"

namespace Forradia {

class cPlanetShaper {
 public:
  explicit cPlanetShaper(const cEngine &Engine_) : Engine(Engine_) {}

  float GetNewY(float Y, float TileX, float TileY);

 private:
  const cEngine &Engine;
};

}  // namespace Forradia
