// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once
#include "cMath3D.h"

namespace Forradia {

class cAlgorithmsVectors {
 public:
  bool InTriangle(cVector3 point, cVector3 tri1, cVector3 tri2,
                         cVector3 tri3);

 private:
  bool SameSide(cVector3 p1, cVector3 p2, cVector3 a, cVector3 b);

  cVector3 GenTriNormal(cVector3 t1, cVector3 t2, cVector3 t3);

  cMath3D Math3D;
};

}  // namespace Forradia
