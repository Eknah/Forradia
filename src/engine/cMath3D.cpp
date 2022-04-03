// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#include "cMath3D.h"
namespace Forradia {

cVector3 cMath3D::Cross(const cVector3 a, const cVector3 b) {
    return cVector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x);
  }

float cMath3D::Magnitude(const cVector3 in) {
    return (sqrtf(powf(in.x, 2) + powf(in.y, 2) + powf(in.z, 2)));
  }

float cMath3D::Dot(const cVector3 a, const cVector3 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
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
