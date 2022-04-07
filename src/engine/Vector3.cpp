// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#include "Vector3.h"

namespace Forradia {

bool cVector3::operator==(const cVector3 &other) const {
  return (this->x == other.x && this->y == other.y && this->z == other.z);
}

bool cVector3::operator!=(const cVector3 &other) const {
  return !(this->x == other.x && this->y == other.y && this->z == other.z);
}

cVector3 cVector3::operator+(const cVector3 &right) const {
  return cVector3(this->x + right.x, this->y + right.y, this->z + right.z);
}

cVector3 cVector3::operator-(const cVector3 &right) const {
  return cVector3(this->x - right.x, this->y - right.y, this->z - right.z);
}

cVector3 cVector3::operator*(const float &other) const {
  return cVector3(this->x * other, this->y * other, this->z * other);
}

cVector3 cVector3::operator/(const float &other) const {
  return cVector3(this->x / other, this->y / other, this->z / other);
}

}  // namespace Forradia
