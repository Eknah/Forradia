#pragma once

namespace Forradia
{

class F_Vector3
{

public:
    F_Vector3() = default;
    F_Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

    inline bool operator==(const F_Vector3& other) const
    {
        return (this->X == other.X && this->Y == other.Y && this->Z == other.Z);
    }

    inline bool operator!=(const F_Vector3& other) const
    {
        return !(this->X == other.X && this->Y == other.Y && this->Z == other.Z);
    }

    inline F_Vector3 operator+(const F_Vector3& right) const
    {
        return F_Vector3(this->X + right.X, this->Y + right.Y, this->Z + right.Z);
    }

    inline F_Vector3 operator-(const F_Vector3& right) const
    {
        return F_Vector3(this->X - right.X, this->Y - right.Y, this->Z - right.Z);
    }

    inline F_Vector3 operator*(const float& other) const
    {
        return F_Vector3(this->X * other, this->Y * other, this->Z * other);
    }

    inline F_Vector3 operator/(const float& other) const
    {
        return F_Vector3(this->X / other, this->Y / other, this->Z / other);
    }

    float X = 0.0f;
    float Y = 0.0f;
    float Z = 0.0f;

};

}
