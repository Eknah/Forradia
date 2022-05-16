// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#include "Math3D.h"
namespace Forradia
{

    Vector3 Math3D::Cross(const Vector3 a, const Vector3 b)
    {
        return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
    }

    float Math3D::Magnitude(const Vector3 in)
    {
        return (sqrtf(powf(in.x, 2) + powf(in.y, 2) + powf(in.z, 2)));
    }

    float Math3D::Dot(const Vector3 a, const Vector3 b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    float Math3D::AngleBetween(const Vector3 a, const Vector3 b)
    {
        float angle = Dot(a, b);
        angle /= (Magnitude(a) * Magnitude(b));
        return acosf(angle);
    }

    Vector3 Math3D::Proj(const Vector3 a, const Vector3 b)
    {
        Vector3 bn = b / Magnitude(b);
        return bn * Dot(a, bn);
    }

}  // namespace Forradia
