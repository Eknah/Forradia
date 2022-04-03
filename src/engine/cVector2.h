// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once
#include "cVector2.h"

namespace Forradia {

class cVector2 {
 public:
  cVector2() = default;
  cVector2(float x, float y) : x(x), y(y) {}

  float x = 0.0f;
  float y = 0.0f;
};

}  // namespace Forradia
