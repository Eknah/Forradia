// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "cVector3.h"
#include <math.h>

namespace Forradia {

class cMath3D {
 public:
  cVector3 Cross(const cVector3 a, const cVector3 b);

  float Magnitude(const cVector3 in);

  float Dot(const cVector3 a, const cVector3 b);

  float AngleBetween(const cVector3 a, const cVector3 b);

  cVector3 Proj(const cVector3 a, const cVector3 b);
};

}  // namespace Forradia
