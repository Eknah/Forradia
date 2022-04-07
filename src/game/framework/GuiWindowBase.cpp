// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "GuiWindowBase.h"
#include "../engine/Engine.h"

namespace Forradia {

void cGuiWindowBase::Render() {
  if (!visible)
    return;

  engine.FillRectangle(palette.mediumBlue, bounds.x, bounds.y, bounds.width,
                       bounds.height);
  engine.DrawRectangle(palette.black, bounds.x, bounds.y, bounds.width,
                       bounds.height);
  engine.DrawString(title, palette.black, bounds.x + margin, bounds.y + margin);
  engine.DrawLine(palette.black, bounds.x, bounds.y + titleBarHeight,
                  bounds.x + bounds.width, bounds.y + titleBarHeight);

  RenderDerived();
}

void cGuiWindowBase::Update() {
  if (!isBeingMoved)
    return;

  auto MousePosF = utilities.GetMousePositionF();
  auto DeltaMouseX = MousePosF.x - startMoveMousePosition.x;
  auto DeltaMouseY = MousePosF.y - startMoveMousePosition.y;

  bounds.x = startMovePosition.x + DeltaMouseX;
  bounds.y = startMovePosition.y + DeltaMouseY;
}

cRectF cGuiWindowBase::GetInteriorBounds() {
  auto X = bounds.x + margin;
  auto Y = bounds.y + titleBarHeight + margin;
  auto Width = bounds.width - 2 * margin;
  auto Height = bounds.height - titleBarHeight - 2 * margin;

  return {X, Y, Width, Height};
}

bool cGuiWindowBase::DoMouseDown(Uint8 MouseButton) {
  if (!visible)
    return false;

  auto MousePosF = utilities.GetMousePositionF();
  auto TitleBarBounds = GetTitleBarBounds();

  if (TitleBarBounds.ContainsPoint(MousePosF)) {
    isBeingMoved = true;
    startMovePosition = {bounds.x, bounds.y};
    startMoveMousePosition = {MousePosF.x, MousePosF.y};
  }

  DoMouseDownDerived(MouseButton);

  if (bounds.ContainsPoint(MousePosF))
    return true;

  return false;
}

cRectF cGuiWindowBase::GetTitleBarBounds() {
  return {bounds.x, bounds.y, bounds.width, titleBarHeight};
}

void cGuiWindowBase::DoMouseUp() { isBeingMoved = false; }

}  // namespace Forradia
