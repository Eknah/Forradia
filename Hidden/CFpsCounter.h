#pragma once
#include "CommonExternal.h"
#include "IEngine.h"
#include "CPalette.h"

namespace Forradia
{

class CFpsCounter
{

public:

    CFpsCounter(IEngine& engine) : Engine(engine) {}

    inline void Update()
    {
        FramesCount++;
        if (Ticks() > TickLastUpdate + 1000)
        {
            Fps = FramesCount;
            FramesCount = 0;
            TickLastUpdate = Ticks();
        }
    }

    inline void Render()
    {
        Engine.FillRectangle(Palette.MediumBlueSemiTrans, Posx - Width / 2, Posy - Height / 2, Width, Height);
        Engine.DrawRectangle(Palette.WhiteSemiTrans, Posx - Width / 2, Posy - Height / 2, Width, Height);
        Engine.DrawString("Fps: " + std::to_string(Fps), Palette.White, Posx, Posy, true);
    }

private:

    IEngine& Engine;
    CPalette Palette;

    int FramesCount = 0;
    int Fps = 0;
    int TickLastUpdate = 0;
    const float Posx = 0.97f;
    const float  Posy = 0.015f;
    const float  Width = 0.07f;
    const float  Height = 0.03f;

};

}
