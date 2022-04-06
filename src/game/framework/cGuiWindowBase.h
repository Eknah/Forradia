// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "../engine/cEngine.h"
#include "../engine/cRectF.h"
#include "../engine/cUtilities.h"

namespace Forradia {

class cGuiWindowBase {
 public:
  cGuiWindowBase(const cEngine &_engine, std::string _tile, cRectF _bounds)
      : engine(_engine), title(_tile), bounds(_bounds) {}

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

  cRectF GetInteriorBounds();

  // To implement in child

  virtual void DoMouseDownDerived(Uint8 MouseButton) = 0;
  virtual void RenderDerived() = 0;

  // Basic data

  const float margin = 0.008f;

  const cEngine &engine;

 private:
  // Internal helpers

  cRectF GetTitleBarBounds();

  // Composition

  cPalette palette;
  cUtilities utilities;

  // Basic data

  std::string title;
  const float titleBarHeight = 0.04f;

  // Dimensions

  cRectF bounds;

  // Window movement

  bool isBeingMoved = false;
  SDL_FPoint startMovePosition = {-1, -1};
  SDL_FPoint startMoveMousePosition = {-1, -1};
};

}  // namespace Forradia
