#pragma once
#include <math.h>
#include "F_Vector3.h"

namespace Forradia
{

class F_Math3D
{

public:

    inline F_Vector3 Cross(const F_Vector3 a, const F_Vector3 b)
    {
        return F_Vector3(a.Y * b.Z - a.Z * b.Y,
                        a.Z * b.X - a.X * b.Z,
                        a.X * b.Y - a.Y * b.X);
    }

    inline float Magnitude(const F_Vector3 in)
    {
        return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
    }

    inline float Dot(const F_Vector3 a, const F_Vector3 b)
    {
        return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
    }

    inline float AngleBetween(const F_Vector3 a, const F_Vector3 b)
    {
        float angle = Dot(a, b);
        angle /= (Magnitude(a) * Magnitude(b));
        return angle = acosf(angle);
    }

    inline F_Vector3 Proj(const F_Vector3 a, const F_Vector3 b)
    {
        F_Vector3 bn = b / Magnitude(b);
        return bn * Dot(a, bn);
    }

};

}
