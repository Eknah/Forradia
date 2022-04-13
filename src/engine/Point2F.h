// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

class Point2F {
 public:
  Point2F(float _x, float y) : x(_x), y(y) {}

  bool IsUndefined();
  void MakeUndefined();

  float x = 0.0f;
  float y = 0.0f;
};

}  // namespace Forradia
