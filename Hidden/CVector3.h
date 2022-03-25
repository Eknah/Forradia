#pragma once

namespace Forradia
{

class CVector3
{

public:

    CVector3() : X(0.0f), Y(0.0f), Z(0.0f) {}
    CVector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

    inline bool operator==(const CVector3& other) const
    {
        return (this->X == other.X && this->Y == other.Y && this->Z == other.Z);
    }

    inline bool operator!=(const CVector3& other) const
    {
        return !(this->X == other.X && this->Y == other.Y && this->Z == other.Z);
    }

    inline CVector3 operator+(const CVector3& right) const
    {
        return CVector3(this->X + right.X, this->Y + right.Y, this->Z + right.Z);
    }

    inline CVector3 operator-(const CVector3& right) const
    {
        return CVector3(this->X - right.X, this->Y - right.Y, this->Z - right.Z);
    }

    inline CVector3 operator*(const float& other) const
    {
        return CVector3(this->X * other, this->Y * other, this->Z * other);
    }

    inline CVector3 operator/(const float& other) const
    {
        return CVector3(this->X / other, this->Y / other, this->Z / other);
    }

    float X;
    float Y;
    float Z;

};

}
