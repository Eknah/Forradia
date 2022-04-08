// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Engine.h"

namespace Forradia {

class PlanetShaper {
 public:
  explicit PlanetShaper(const Engine &_e) : e(_e) {}

  float GetNewY(float y, float tilex, float tiley);

 private:
  const Engine &e;
};

}  // namespace Forradia
