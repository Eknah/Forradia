// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once

#include "Math3D.h"

namespace Forradia
{
    class AlgorithmsVectors
    {
    public:
        bool InTriangle(
			Vector3 point,
			Vector3 tri1,
			Vector3 tri2,
            Vector3 tri3
		);

    private:
        bool SameSide(
			Vector3 p1,
			Vector3 p2,
			Vector3 a,
			Vector3 b
		);
		
        Vector3 GenTriNormal(
			Vector3 t1,
			Vector3 t2,
			Vector3 t3
		);

        Math3D math3D;
    };
}
