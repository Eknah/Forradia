// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "cPalette.h"

namespace Forradia {

class iEngine;

class iFpsCounter {
 public:
  explicit iFpsCounter(iEngine &_engine) : engine(_engine) {}

  virtual void Update() = 0;
  virtual void Render() = 0;

 protected:
  iEngine &engine;
  cPalette palette;

  int framesCount = 0;
  int fps = 0;
  unsigned int tickLastUpdate = 0;
  const float width = 0.07f;
  const float height = 0.03f;
  const float posx = 0.97f;
  const float posy = 1.0f - height/2;
};

}  // namespace Forradia
