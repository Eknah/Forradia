#pragma once
#include "CommonExternal.h"
#include "F_Math3D.h"

namespace Forradia
{

class F_VectorAlgorithms
{

public:

    inline bool InTriangle(F_Vector3 point, F_Vector3 tri1, F_Vector3 tri2, F_Vector3 tri3)
    {
        bool within_tri_prisim = SameSide(point, tri1, tri2, tri3) && SameSide(point, tri2, tri1, tri3)
                && SameSide(point, tri3, tri1, tri2);

        if (!within_tri_prisim)
            return false;

        F_Vector3 n = GenTriNormal(tri1, tri2, tri3);

        F_Vector3 proj = Math3D.Proj(point, n);

        if (Math3D.Magnitude(proj) == 0)
            return true;
        else
            return false;
    }

private:

    inline bool SameSide(F_Vector3 p1, F_Vector3 p2, F_Vector3 a, F_Vector3 b)
    {
        F_Vector3 cp1 = Math3D.Cross(b - a, p1 - a);
        F_Vector3 cp2 = Math3D.Cross(b - a, p2 - a);

        if (Math3D.Dot(cp1, cp2) >= 0)
            return true;
        else
            return false;
    }

    inline F_Vector3 GenTriNormal(F_Vector3 t1, F_Vector3 t2, F_Vector3 t3)
    {
        F_Vector3 u = t2 - t1;
        F_Vector3 v = t3 - t1;

        F_Vector3 Normal = Math3D.Cross(u, v);

        return Normal;
    }

    F_Math3D Math3D;

};

}
