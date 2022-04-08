// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once
#include "Vector3.h"
#include <math.h>

namespace Forradia {

class Math3D {
 public:
  Vector3 Cross(const Vector3 a, const Vector3 b);

  float Magnitude(const Vector3 in);

  float Dot(const Vector3 a, const Vector3 b);

  float AngleBetween(const Vector3 a, const Vector3 b);

  Vector3 Proj(const Vector3 a, const Vector3 b);
};

}  // namespace Forradia
