// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "cVector2.h"
#include "cVector3.h"

namespace Forradia {

class cVertex {
 public:
  cVector3 Position;
  cVector3 Normal;
  cVector2 TextureCoordinate;
};

}  // namespace Forradia
