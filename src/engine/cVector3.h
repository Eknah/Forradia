// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia
{

class cVector3
{

public:
    cVector3() = default;
    cVector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

    inline bool operator==(const cVector3& other) const
    {
        return (this->X == other.X && this->Y == other.Y && this->Z == other.Z);
    }

    inline bool operator!=(const cVector3& other) const
    {
        return !(this->X == other.X && this->Y == other.Y && this->Z == other.Z);
    }

    inline cVector3 operator+(const cVector3& right) const
    {
        return cVector3(this->X + right.X, this->Y + right.Y, this->Z + right.Z);
    }

    inline cVector3 operator-(const cVector3& right) const
    {
        return cVector3(this->X - right.X, this->Y - right.Y, this->Z - right.Z);
    }

    inline cVector3 operator*(const float& other) const
    {
        return cVector3(this->X * other, this->Y * other, this->Z * other);
    }

    inline cVector3 operator/(const float& other) const
    {
        return cVector3(this->X / other, this->Y / other, this->Z / other);
    }

    float X = 0.0f;
    float Y = 0.0f;
    float Z = 0.0f;

};

}
