// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "cVector2.h"

namespace Forradia {

class cVector2 {
 public:
  cVector2() = default;
  cVector2(float x, float y) : X(x), Y(y) {}

  float X = 0.0f;
  float Y = 0.0f;
};

}  // namespace Forradia
