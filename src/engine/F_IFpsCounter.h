
#pragma once
#include "CommonExternal.h"
#include "F_Palette.h"

namespace Forradia
{

class F_IEngine;

class F_IFpsCounter
{

public:

    F_IFpsCounter(F_IEngine& engine) : Engine(engine) {}

    inline virtual void Update()= 0;
    inline virtual void Render() = 0;

protected:

    F_IEngine& Engine;
    F_Palette Palette;

    int FramesCount = 0;
    int Fps = 0;
    unsigned int TickLastUpdate = 0;
    const float Posx = 0.97f;
    const float  Posy = 0.015f;
    const float  Width = 0.07f;
    const float  Height = 0.03f;

};

}
