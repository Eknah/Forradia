// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "GuiWindowBase.h"
#include "../engine/Engine.h"

namespace Forradia {

void GuiWindowBase::Render() {
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

void GuiWindowBase::Update() {
  if (!isBeingMoved)
    return;

  auto mousePosF = utilities.GetMousePositionF();
  auto deltaMouseX = mousePosF.x - startMoveMousePosition.x;
  auto deltaMouseY = mousePosF.y - startMoveMousePosition.y;

  bounds.x = startMovePosition.x + deltaMouseX;
  bounds.y = startMovePosition.y + deltaMouseY;
}

RectF GuiWindowBase::GetInteriorBounds() {
  auto x = bounds.x + margin;
  auto y = bounds.y + titleBarHeight + margin;
  auto width = bounds.width - 2 * margin;
  auto height = bounds.height - titleBarHeight - 2 * margin;

  return {x, y, width, height};
}

bool GuiWindowBase::DoMouseDown(Uint8 mouseButton) {
  if (!visible)
    return false;

  auto mousePosF = utilities.GetMousePositionF();
  auto titleBarBounds = GetTitleBarBounds();

  if (titleBarBounds.ContainsPoint(mousePosF)) {
    isBeingMoved = true;
    startMovePosition = {bounds.x, bounds.y};
    startMoveMousePosition = {mousePosF.x, mousePosF.y};
  }

  DoMouseDownDerived(mouseButton);

  if (bounds.ContainsPoint(mousePosF))
    return true;

  return false;
}

RectF GuiWindowBase::GetTitleBarBounds() {
  return {bounds.x, bounds.y, bounds.width, titleBarHeight};
}

void GuiWindowBase::DoMouseUp() {
    isBeingMoved = false;
}

}  // namespace Forradia
