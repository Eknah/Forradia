// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "cVector3.h"
#include <math.h>

namespace Forradia {

class cMath3D {
 public:
  inline cVector3 Cross(const cVector3 a, const cVector3 b) {
    return cVector3(a.Y * b.Z - a.Z * b.Y, a.Z * b.X - a.X * b.Z,
                    a.X * b.Y - a.Y * b.X);
  }

  inline float Magnitude(const cVector3 in) {
    return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
  }

  inline float Dot(const cVector3 a, const cVector3 b) {
    return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
  }

  inline float AngleBetween(const cVector3 a, const cVector3 b) {
    float angle = Dot(a, b);
    angle /= (Magnitude(a) * Magnitude(b));
    return angle = acosf(angle);
  }

  inline cVector3 Proj(const cVector3 a, const cVector3 b) {
    cVector3 bn = b / Magnitude(b);
    return bn * Dot(a, bn);
  }
};

}  // namespace Forradia
