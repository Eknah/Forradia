// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/iEngine.h"
#include "iFpsCounter.h"

namespace Forradia {

class cFpsCounter : public iFpsCounter {
 public:
  explicit cFpsCounter(iEngine &engine) : iFpsCounter(engine) {}

  inline void Update() override {
    FramesCount++;
    if (Ticks() > TickLastUpdate + 1000) {
      Fps = FramesCount;
      FramesCount = 0;
      TickLastUpdate = Ticks();
    }
  }

  inline void Render() override {
    Engine.FillRectangle(Palette.MediumBlueSemiTrans, Posx - Width / 2,
                         Posy - Height / 2, Width, Height);
    Engine.DrawRectangle(Palette.WhiteSemiTrans, Posx - Width / 2,
                         Posy - Height / 2, Width, Height);
    Engine.DrawString("Fps: " + std::to_string(Fps), Palette.White, Posx, Posy,
                      true);
  }
};

}  // namespace Forradia
