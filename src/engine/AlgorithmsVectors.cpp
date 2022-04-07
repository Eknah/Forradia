// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#include "AlgorithmsVectors.h"

namespace Forradia {

bool cAlgorithmsVectors::InTriangle(cVector3 point, cVector3 tri1, cVector3 tri2,
                       cVector3 tri3) {
  bool withinTriPrisim = SameSide(point, tri1, tri2, tri3) &&
                           SameSide(point, tri2, tri1, tri3) &&
                           SameSide(point, tri3, tri1, tri2);

  if (!withinTriPrisim)
    return false;

  cVector3 n = GenTriNormal(tri1, tri2, tri3);

  cVector3 proj = math3D.Proj(point, n);

  if (math3D.Magnitude(proj) == 0)
    return true;
  else
    return false;
}

bool cAlgorithmsVectors::SameSide(cVector3 p1, cVector3 p2, cVector3 a, cVector3 b) {
  cVector3 cp1 = math3D.Cross(b - a, p1 - a);
  cVector3 cp2 = math3D.Cross(b - a, p2 - a);

  if (math3D.Dot(cp1, cp2) >= 0)
    return true;
  else
    return false;
}

cVector3 cAlgorithmsVectors::GenTriNormal(cVector3 t1, cVector3 t2, cVector3 t3) {
  cVector3 u = t2 - t1;
  cVector3 v = t3 - t1;

  cVector3 normal = math3D.Cross(u, v);

  return normal;
}

}  // namespace Forradia
