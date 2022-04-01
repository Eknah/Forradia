// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cRectF.h"

namespace Forradia {

bool cRectF::ContainsPoint(cPoint2F point) {
    if (point.X >= X && point.Y >= Y && point.X < X + Width &&
        point.Y < Y + Height)
      return true;

    return false;
  }

}  // namespace Forradia
