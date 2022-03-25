#pragma once
namespace Forradia
{

class CMouseHandler
{

public:
    void ResetForNewFrame();

    float WheelAmount = 0;
    bool LeftButtonDown = False;
    bool RightButtonDown = False;

};

}
