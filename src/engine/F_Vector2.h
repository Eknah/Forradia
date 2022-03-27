
#pragma once
#include "F_Vector2.h"

namespace Forradia
{

class F_Vector2
{

public:
    F_Vector2() = default;
    F_Vector2(float x, float y) : X(x), Y(y) {}

    float X = 0.0f;
    float Y = 0.0f;
};

}
