#pragma once
#include "CVector2.h"

namespace Forradia
{

class CVector2
{

public:
    CVector2() = default;
    CVector2(float x, float y) : X(x), Y(y) {}

    float X = 0.0f;
    float Y = 0.0f;
};

}
