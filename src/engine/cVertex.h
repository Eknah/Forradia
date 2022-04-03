// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once
#include "cVector2.h"
#include "cVector3.h"

namespace Forradia {

class cVertex {
 public:
  cVector3 position;
  cVector3 normal;
  cVector2 textureCoordinate;
};

}  // namespace Forradia
