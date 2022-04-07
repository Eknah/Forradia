// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "Point2F.h"

namespace Forradia {

class cRectF {
 public:
  bool ContainsPoint(cPoint2F point);

  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
};

}  // namespace Forradia
