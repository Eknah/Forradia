// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once
#include "Vector2.h"

namespace Forradia {

class Vector2 {
 public:
  Vector2() = default;
  Vector2(float _x, float _y) : x(_x), y(_y) {}

  float x = 0.0f;
  float y = 0.0f;
};

}  // namespace Forradia
