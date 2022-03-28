// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "CommonExternal.h"
#include "cPalette.h"

namespace Forradia {

class iEngine;

class iFpsCounter {
 public:
  explicit iFpsCounter(iEngine &engine) : Engine(engine) {}

  inline virtual void Update() = 0;
  inline virtual void Render() = 0;

 protected:
  iEngine &Engine;
  cPalette Palette;

  int FramesCount = 0;
  int Fps = 0;
  unsigned int TickLastUpdate = 0;
  const float Posx = 0.97f;
  const float Posy = 0.015f;
  const float Width = 0.07f;
  const float Height = 0.03f;
};

}  // namespace Forradia
