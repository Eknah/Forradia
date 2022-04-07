// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Engine.h"

namespace Forradia {

class cPlanetShaper {
 public:
  explicit cPlanetShaper(const cEngine &_engine) : engine(_engine) {}

  float GetNewY(float y, float tilex, float tiley);

 private:
  const cEngine &engine;
};

}  // namespace Forradia
