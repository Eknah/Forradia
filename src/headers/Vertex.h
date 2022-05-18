// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace Forradia
{
    class Vertex
    {
    public:
        Vector3 position;
        Vector3 normal;
        Vector2 textureCoordinate;
    };
}