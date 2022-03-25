#pragma once
#include <math.h>
#include "CVector3.h"

namespace Forradia
{
class CMath3D
{

public:
    inline CVector3 Cross(const CVector3 a, const CVector3 b)
    {
        return CVector3(a.Y * b.Z - a.Z * b.Y,
                        a.Z * b.X - a.X * b.Z,
                        a.X * b.Y - a.Y * b.X);
    }
    inline float Magnitude(const CVector3 in)
    {
        return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
    }
    inline float Dot(const CVector3 a, const CVector3 b)
    {
        return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
    }
    inline float AngleBetween(const CVector3 a, const CVector3 b)
    {
        float angle = Dot(a, b);
        angle /= (Magnitude(a) * Magnitude(b));
        return angle = acosf(angle);
    }
    inline CVector3 Proj(const CVector3 a, const CVector3 b)
    {
        CVector3 bn = b / Magnitude(b);
        return bn * Dot(a, bn);
    }

};
}
