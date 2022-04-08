// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "SDL2/SDL.h"
#include "TextRect.h"
#include <vector>

namespace Forradia {

class Engine;

class SceneBase {
 public:
  explicit SceneBase(const Engine &_engine) : engine(_engine) {}

  // To implement in child

  virtual void Enter() = 0;
  virtual void Update() = 0;
  virtual void Render() = 0;
  virtual void DoMouseDown(Uint8 MouseButton) = 0;
  virtual void DoMouseUp(Uint8 MouseButton) = 0;

 protected:
  const Engine &engine;

  std::vector<TextRect> sceneButtons;
};

}  // namespace Forradia
