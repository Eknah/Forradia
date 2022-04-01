// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once

namespace Forradia {

class cVector3 {
 public:
  cVector3() = default;
  cVector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

  bool operator==(const cVector3 &other) const;
  bool operator!=(const cVector3 &other) const;
  cVector3 operator+(const cVector3 &right) const;
  cVector3 operator-(const cVector3 &right) const;
  cVector3 operator*(const float &other) const;
  cVector3 operator/(const float &other) const;

  float X = 0.0f;
  float Y = 0.0f;
  float Z = 0.0f;
};

}  // namespace Forradia
