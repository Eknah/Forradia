// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cGuiWindowBase.h"
#include "../engine/cEngine.h"

namespace Forradia {

void cGuiWindowBase::Render() {
  if (!Visible)
    return;

  Engine.FillRectangle(Palette.mediumBlue, Bounds.x, Bounds.y, Bounds.width,
                       Bounds.height);
  Engine.DrawRectangle(Palette.black, Bounds.x, Bounds.y, Bounds.width,
                       Bounds.height);
  Engine.DrawString(Title, Palette.black, Bounds.x + Margin, Bounds.y + Margin);
  Engine.DrawLine(Palette.black, Bounds.x, Bounds.y + TitleBarHeight,
                  Bounds.x + Bounds.width, Bounds.y + TitleBarHeight);

  RenderDerived();
}

void cGuiWindowBase::Update() {
  if (!IsBeingMoved)
    return;

  auto MousePosF = Utilities.GetMousePositionF();
  auto DeltaMouseX = MousePosF.x - StartMoveMousePosition.x;
  auto DeltaMouseY = MousePosF.y - StartMoveMousePosition.y;

  Bounds.x = StartMovePosition.x + DeltaMouseX;
  Bounds.y = StartMovePosition.y + DeltaMouseY;
}

cRectF cGuiWindowBase::GetInteriorBounds() {
  auto X = Bounds.x + Margin;
  auto Y = Bounds.y + TitleBarHeight + Margin;
  auto Width = Bounds.width - 2 * Margin;
  auto Height = Bounds.height - TitleBarHeight - 2 * Margin;

  return {X, Y, Width, Height};
}

bool cGuiWindowBase::DoMouseDown(Uint8 MouseButton) {
  if (!Visible)
    return false;

  auto MousePosF = Utilities.GetMousePositionF();
  auto TitleBarBounds = GetTitleBarBounds();

  if (TitleBarBounds.ContainsPoint(MousePosF)) {
    IsBeingMoved = true;
    StartMovePosition = {Bounds.x, Bounds.y};
    StartMoveMousePosition = {MousePosF.x, MousePosF.y};
  }

  DoMouseDownDerived(MouseButton);

  if (Bounds.ContainsPoint(MousePosF))
    return true;

  return false;
}

cRectF cGuiWindowBase::GetTitleBarBounds() {
  return {Bounds.x, Bounds.y, Bounds.width, TitleBarHeight};
}

void cGuiWindowBase::DoMouseUp() { IsBeingMoved = false; }

}  // namespace Forradia
