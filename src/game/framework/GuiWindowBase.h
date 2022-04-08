// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "../engine/Engine.h"
#include "../engine/RectF.h"
#include "../engine/Utilities.h"

namespace Forradia {

class GuiWindowBase {
 public:
  GuiWindowBase(const Engine &_e, std::string _tile, RectF _bounds)
      : e(_e), title(_tile), bounds(_bounds) {}

  // Looped operations

  void Render();
  void Update();

  // Fired by events

  bool DoMouseDown(Uint8 MouseButton);
  void DoMouseUp();

  // Basic data

  bool visible = false;

 protected:
  // Internal helpers

  RectF GetInteriorBounds();

  // To implement in child

  virtual void DoMouseDownDerived(Uint8 MouseButton) = 0;
  virtual void RenderDerived() = 0;

  // Basic data

  const float margin = 0.008f;

  const Engine &e;

 private:
  // Internal helpers

  RectF GetTitleBarBounds();

  // Composition

  Palette palette;
  Utilities utilities;

  // Basic data

  std::string title;
  const float titleBarHeight = 0.04f;

  // Dimensions

  RectF bounds;

  // Window movement

  bool isBeingMoved = false;
  SDL_FPoint startMovePosition = {-1, -1};
  SDL_FPoint startMoveMousePosition = {-1, -1};
};

}  // namespace Forradia
