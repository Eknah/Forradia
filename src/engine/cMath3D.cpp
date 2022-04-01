// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cMath3D.h"
namespace Forradia {

cVector3 cMath3D::Cross(const cVector3 a, const cVector3 b) {
    return cVector3(a.Y * b.Z - a.Z * b.Y, a.Z * b.X - a.X * b.Z,
                    a.X * b.Y - a.Y * b.X);
  }

float cMath3D::Magnitude(const cVector3 in) {
    return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
  }

float cMath3D::Dot(const cVector3 a, const cVector3 b) {
    return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
  }

float cMath3D::AngleBetween(const cVector3 a, const cVector3 b) {
    float angle = Dot(a, b);
    angle /= (Magnitude(a) * Magnitude(b));
    return acosf(angle);
  }

cVector3 cMath3D::Proj(const cVector3 a, const cVector3 b) {
    cVector3 bn = b / Magnitude(b);
    return bn * Dot(a, bn);
  }

}  // namespace Forradia
