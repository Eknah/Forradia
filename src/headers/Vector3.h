// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once

namespace Forradia
{
    class Vector3
    {
    public:
        Vector3() = default;
        Vector3(float x_, float y_, float z_)
		: x(x_), y(y_), z(z_) {}

        bool operator==(const Vector3& other) const;
        bool operator!=(const Vector3& other) const;
        Vector3 operator+(const Vector3& right) const;
        Vector3 operator-(const Vector3& right) const;
        Vector3 operator*(const float& other) const;
        Vector3 operator/(const float& other) const;

        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };
}