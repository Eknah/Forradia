#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class CMouseHandler
{

public:

    // Game loop related
    void ResetForNewFrame();

    float WheelAmount = 0;
    bool LeftButtonDown = false;
    bool RightButtonDown = false;

};

}
