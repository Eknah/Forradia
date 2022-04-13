// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "FpsCounter.h"

namespace Forradia
{

    void FpsCounter::Update()
    {
        framesCount++;
        if (timer.HasFinished())
        {
            fps = framesCount;
            framesCount = 0;
            timer.Reset();
        }
    }

    void FpsCounter::Render()
    {
        e.FillRect(palette.mediumBlueSemiTrans, posx - w / 2,
            posy - h / 2, w, h);
        e.DrawRect(palette.whiteSemiTrans, posx - w / 2,
            posy - h / 2, w, h);
        e.DrawString("Fps: " + std::to_string(fps), palette.white, posx, posy,
            true);
    }

}  // namespace Forradia
