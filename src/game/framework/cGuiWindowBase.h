// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cEngine.h"
#include "../engine/cRectF.h"
#include "../engine/cUtilities.h"

namespace Forradia {

class cGuiWindowBase {

public:
  cGuiWindowBase(cEngine &Engine_, std::string Title_, cRectF Bounds_)
      : Engine(Engine_), Title(Title_), Bounds(Bounds_) {}

  // Looped operations

  void Render();
  void Update();

  // Fired by events

  bool DoMouseDown(Uint8 MouseButton);
  void DoMouseUp();

  // Basic data

  bool Visible = false;

protected:
  // Internal helpers

  cRectF GetInteriorBounds();

  // To implement in child

  virtual void DoMouseDownDerived(Uint8 MouseButton) = 0;
  virtual void RenderDerived() = 0;

  // Basic data

  const float Margin = 0.008f;

  cEngine &Engine;

private:
  // Internal helpers

  cRectF GetTitleBarBounds();

  // Composition

  cPalette Palette;
  cUtilities Utilities;

  // Basic data

  std::string Title;
  const float TitleBarHeight = 0.04f;

  // Dimensions

  cRectF Bounds;

  // Window movement

  bool IsBeingMoved = false;
  SDL_FPoint StartMovePosition = {-1, -1};
  SDL_FPoint StartMoveMousePosition = {-1, -1};
};

} // namespace Forradia
