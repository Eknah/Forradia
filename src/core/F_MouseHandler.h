
#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class F_MouseHandler
{

public:

    // Game loop related

    inline void ResetForNewFrame()
    {
        WheelAmount *= 0.85f;

        if (std::abs(WheelAmount) < 0.1f)
            WheelAmount = 0;
    }

    float WheelAmount = 0;
    bool LeftButtonDown = false;
    bool RightButtonDown = false;

};

}
