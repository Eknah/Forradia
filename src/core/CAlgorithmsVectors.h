#pragma once
#include "CommonExternal.h"
#include "CMath3D.h"

namespace Forradia
{

class CVectorAlgorithms
{

public:

    inline bool InTriangle(CVector3 point, CVector3 tri1, CVector3 tri2, CVector3 tri3)
    {
        bool within_tri_prisim = SameSide(point, tri1, tri2, tri3) && SameSide(point, tri2, tri1, tri3)
                && SameSide(point, tri3, tri1, tri2);

        if (!within_tri_prisim)
            return false;

        CVector3 n = GenTriNormal(tri1, tri2, tri3);

        CVector3 proj = Math3D.Proj(point, n);

        if (Math3D.Magnitude(proj) == 0)
            return true;
        else
            return false;
    }

private:

    inline bool SameSide(CVector3 p1, CVector3 p2, CVector3 a, CVector3 b)
    {
        CVector3 cp1 = Math3D.Cross(b - a, p1 - a);
        CVector3 cp2 = Math3D.Cross(b - a, p2 - a);

        if (Math3D.Dot(cp1, cp2) >= 0)
            return true;
        else
            return false;
    }

    inline CVector3 GenTriNormal(CVector3 t1, CVector3 t2, CVector3 t3)
    {
        CVector3 u = t2 - t1;
        CVector3 v = t3 - t1;

        CVector3 Normal = Math3D.Cross(u, v);

        return Normal;
    }

    CMath3D Math3D;

};

}
