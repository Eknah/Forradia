// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "CommonExternal.h"
#include "cMath3D.h"

namespace Forradia {

class cVectorAlgorithms {
 public:
  inline bool InTriangle(cVector3 point, cVector3 tri1, cVector3 tri2,
                         cVector3 tri3) {
    bool within_tri_prisim = SameSide(point, tri1, tri2, tri3) &&
                             SameSide(point, tri2, tri1, tri3) &&
                             SameSide(point, tri3, tri1, tri2);

    if (!within_tri_prisim)
      return false;

    cVector3 n = GenTriNormal(tri1, tri2, tri3);

    cVector3 proj = Math3D.Proj(point, n);

    if (Math3D.Magnitude(proj) == 0)
      return true;
    else
      return false;
  }

 private:
  inline bool SameSide(cVector3 p1, cVector3 p2, cVector3 a, cVector3 b) {
    cVector3 cp1 = Math3D.Cross(b - a, p1 - a);
    cVector3 cp2 = Math3D.Cross(b - a, p2 - a);

    if (Math3D.Dot(cp1, cp2) >= 0)
      return true;
    else
      return false;
  }

  inline cVector3 GenTriNormal(cVector3 t1, cVector3 t2, cVector3 t3) {
    cVector3 u = t2 - t1;
    cVector3 v = t3 - t1;

    cVector3 Normal = Math3D.Cross(u, v);

    return Normal;
  }

  cMath3D Math3D;
};

}  // namespace Forradia
