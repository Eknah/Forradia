#include "Common.h"
#include "CMouseHandler.h"
namespace Forradia
{
void CMouseHandler::ResetForNewFrame()
{
    WheelAmount *= 0.85f;
    if (std::abs(WheelAmount) < 0.1f)
        WheelAmount = 0;
}
}
