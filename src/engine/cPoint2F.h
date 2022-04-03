// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

class cPoint2F {
 public:
  cPoint2F(float X, float Y) : x(X), y(Y) {}

  float x = 0.0f;
  float y = 0.0f;
};

}  // namespace Forradia
