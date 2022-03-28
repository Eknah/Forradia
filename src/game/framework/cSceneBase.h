// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "SDL2/SDL.h"

namespace Forradia {

class cEngine;

class cSceneBase {
 public:
  explicit cSceneBase(cEngine &Engine_) : Engine(Engine_) {}

  // To implement in child

  virtual void Enter() = 0;
  virtual void Update() = 0;
  virtual void Render() = 0;
  virtual void DoMouseDown(Uint8 MouseButton) = 0;
  virtual void DoMouseUp(Uint8 MouseButton) = 0;

 protected:
  cEngine &Engine;
};

}  // namespace Forradia
