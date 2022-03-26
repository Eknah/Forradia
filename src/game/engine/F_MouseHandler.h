
#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class F_MouseHandler
{

public:

    // Game loop related
    void ResetForNewFrame();

    float WheelAmount = 0;
    bool LeftButtonDown = false;
    bool RightButtonDown = false;

};

}
