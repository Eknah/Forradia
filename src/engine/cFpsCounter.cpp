// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cFpsCounter.h"

namespace Forradia {

void cFpsCounter::Update() {
    FramesCount++;
    if (Ticks() > TickLastUpdate + 1000) {
      Fps = FramesCount;
      FramesCount = 0;
      TickLastUpdate = Ticks();
    }
  }

void cFpsCounter::Render() {
    Engine.FillRectangle(Palette.mediumBlueSemiTrans, Posx - Width / 2,
                         Posy - Height / 2, Width, Height);
    Engine.DrawRectangle(Palette.whiteSemiTrans, Posx - Width / 2,
                         Posy - Height / 2, Width, Height);
    Engine.DrawString("Fps: " + std::to_string(Fps), Palette.white, Posx, Posy,
                      true);
  }

}  // namespace Forradia