
#pragma once
#include "F_Point2F.h"

namespace Forradia
{

class F_RectF
{

public:

    inline bool ContainsPoint(F_Point2F point)
    {
        if (point.X >= X && point.Y >= Y && point.X < X + Width && point.Y < Y + Height)
            return true;

        return false;
    }

    float X = 0.0f;
    float Y = 0.0f;
    float Width = 0.0f;
    float Height = 0.0f;
};

}
