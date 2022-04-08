// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "FpsCounter.h"

namespace Forradia {

void FpsCounter::Update() {
    framesCount++;
    if (Ticks() > tickLastUpdate + 1000) {
      fps = framesCount;
      framesCount = 0;
      tickLastUpdate = Ticks();
    }
  }

void FpsCounter::Render() {
    engine.FillRectangle(palette.mediumBlueSemiTrans, posx - width / 2,
                         posy - height / 2, width, height);
    engine.DrawRectangle(palette.whiteSemiTrans, posx - width / 2,
                         posy - height / 2, width, height);
    engine.DrawString("Fps: " + std::to_string(fps), palette.white, posx, posy,
                      true);
  }

}  // namespace Forradia
