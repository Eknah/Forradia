// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "Palette.h"

namespace Forradia {

class IEngine;

class IFpsCounter {
 public:
  explicit IFpsCounter(IEngine &_e) : e(_e) {}

  virtual void Update() = 0;
  virtual void Render() = 0;

 protected:
  IEngine &e;
  Palette palette;

  int framesCount = 0;
  int fps = 0;
  const float width = 0.07f;
  const float height = 0.03f;
  const float posx = 0.97f;
  const float posy = 1.0f - height/2;
};

}  // namespace Forradia
