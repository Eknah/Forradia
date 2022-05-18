// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#include "AlgorithmsVectors.h"

namespace Forradia
{
    bool AlgorithmsVectors::InTriangle (
		Vector3 point,
		Vector3 tri1,
		Vector3 tri2,
		Vector3 tri3
	)
    {
        bool withinTriPrisim =
		SameSide(point, tri1, tri2, tri3)
		&& SameSide(point, tri2, tri1, tri3)
		&& SameSide(point, tri3, tri1, tri2);

        if (!withinTriPrisim)
            return false;

        Vector3 n = GenTriNormal(tri1, tri2, tri3);

        Vector3 proj = math3D.Proj(point, n);

        if (math3D.Magnitude(proj) == 0)
            return true;
        else
            return false;
    }

    bool AlgorithmsVectors::SameSide (
		Vector3 p1,
		Vector3 p2,
		Vector3 a,
		Vector3 b
	)
    {
        Vector3 cp1 = math3D.Cross(b - a, p1 - a);
        Vector3 cp2 = math3D.Cross(b - a, p2 - a);

        if (math3D.Dot(cp1, cp2) >= 0)
            return true;
        else
            return false;
    }

    Vector3 AlgorithmsVectors::GenTriNormal (
		Vector3 t1,
		Vector3 t2,
		Vector3 t3
	)
    {
        Vector3 u = t2 - t1;
        Vector3 v = t3 - t1;

        Vector3 normal = math3D.Cross(u, v);

        return normal;
    }
}