// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "cPalette.h"

namespace Forradia {

class iEngine;

class iFpsCounter {
 public:
  explicit iFpsCounter(iEngine &engine) : Engine(engine) {}

  virtual void Update() = 0;
  virtual void Render() = 0;

 protected:
  iEngine &Engine;
  cPalette Palette;

  int FramesCount = 0;
  int Fps = 0;
  unsigned int TickLastUpdate = 0;
  const float Width = 0.07f;
  const float Height = 0.03f;
  const float Posx = 0.97f;
  const float Posy = 1.0f - Height/2;
};

}  // namespace Forradia
