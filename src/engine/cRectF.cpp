// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cRectF.h"

namespace Forradia {

bool cRectF::ContainsPoint(cPoint2F point) {
    if (point.x >= x && point.y >= y && point.x < x + width &&
        point.y < y + height)
      return true;

    return false;
  }

}  // namespace Forradia
