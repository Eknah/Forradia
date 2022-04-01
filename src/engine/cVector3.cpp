// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#include "cVector3.h"

namespace Forradia {

bool cVector3::operator==(const cVector3 &other) const {
  return (this->X == other.X && this->Y == other.Y && this->Z == other.Z);
}

bool cVector3::operator!=(const cVector3 &other) const {
  return !(this->X == other.X && this->Y == other.Y && this->Z == other.Z);
}

cVector3 cVector3::operator+(const cVector3 &right) const {
  return cVector3(this->X + right.X, this->Y + right.Y, this->Z + right.Z);
}

cVector3 cVector3::operator-(const cVector3 &right) const {
  return cVector3(this->X - right.X, this->Y - right.Y, this->Z - right.Z);
}

cVector3 cVector3::operator*(const float &other) const {
  return cVector3(this->X * other, this->Y * other, this->Z * other);
}

cVector3 cVector3::operator/(const float &other) const {
  return cVector3(this->X / other, this->Y / other, this->Z / other);
}

}  // namespace Forradia
