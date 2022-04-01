// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "cPoint2F.h"

namespace Forradia {

class cRectF {
 public:
  bool ContainsPoint(cPoint2F point);

  float X = 0.0f;
  float Y = 0.0f;
  float Width = 0.0f;
  float Height = 0.0f;
};

}  // namespace Forradia
