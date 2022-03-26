
#pragma once
#include "../core/F_IEngine.h"
#include "F_IFpsCounter.h"

namespace Forradia
{

class F_FpsCounter : public F_IFpsCounter
{

public:

    F_FpsCounter(F_IEngine& engine) : F_IFpsCounter(engine) {}

    inline void Update() override
    {
        FramesCount++;
        if (Ticks() > TickLastUpdate + 1000)
        {
            Fps = FramesCount;
            FramesCount = 0;
            TickLastUpdate = Ticks();
        }
    }

    inline void Render() override
    {
        Engine.FillRectangle(Palette.MediumBlueSemiTrans, Posx - Width / 2, Posy - Height / 2, Width, Height);
        Engine.DrawRectangle(Palette.WhiteSemiTrans, Posx - Width / 2, Posy - Height / 2, Width, Height);
        Engine.DrawString("Fps: " + std::to_string(Fps), Palette.White, Posx, Posy, true);
    }

};

}
