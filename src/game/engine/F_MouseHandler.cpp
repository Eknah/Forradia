#include "CommonExternal.h"
#include "F_MouseHandler.h"

namespace Forradia
{

void F_MouseHandler::ResetForNewFrame()
{
    WheelAmount *= 0.85f;

    if (std::abs(WheelAmount) < 0.1f)
        WheelAmount = 0;
}

}
