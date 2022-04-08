// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "Gui.h"
#include "../engine/Engine.h"
#include "GuiWindowInventory.h"
#include "GuiWindowMall.h"

namespace Forradia {

void cGui::Initialize() {
  windows.clear();
  windows.insert(
      {"Inventory", std::make_unique<cGuiWindowInventory>(
                        engine, "Inventory", cRectF{0.1f, 0.1f, 0.2f, 0.7f})});
  windows.insert(
      {"Mall", std::make_unique<cGuiWindowMall>(
                        engine, "Mall", cRectF{0.2f, 0.1f, 0.7f, 0.6f})});
}

void cGui::Update() {
  auto mousePositionF = utilities.GetMousePositionF();

  if (boundsButtonInventory.ContainsPoint(mousePositionF))
    engine.customCursor.cursorType = eCursorTypes::Hovering;

  if (boundsButtonCharacter.ContainsPoint(mousePositionF))
    engine.customCursor.cursorType = eCursorTypes::Hovering;

  if (boundsButtonSystem.ContainsPoint(mousePositionF))
    engine.customCursor.cursorType = eCursorTypes::Hovering;

  auto mallIconSize = utilities.ConvertToFloat(buttonMallSize);

  auto mallIconBounds = cRectF {1.0f - mallIconSize.width, 0.0f, mallIconSize.width, mallIconSize.height};

  if (mallIconBounds.ContainsPoint(mousePositionF))
    engine.customCursor.cursorType = eCursorTypes::Hovering;

  for (auto &[key, window] : windows)
    window->Update();
}

void cGui::Render() {
  guiMinimap.Render();

  auto MousePositionF = utilities.GetMousePositionF();



  auto mallIconSize = utilities.ConvertToFloat(buttonMallSize);

  auto mallIconBounds = cRectF {1.0f - mallIconSize.width, 0.0f, mallIconSize.width, mallIconSize.height};

  if (mallIconBounds.ContainsPoint(MousePositionF))
    engine.DrawImage("GuiIconMallHovered", 1.0f - mallIconSize.width, 0.0f, mallIconSize.width, mallIconSize.height);
  else
      engine.DrawImage("GuiIconMall", 1.0f - mallIconSize.width, 0.0f, mallIconSize.width, mallIconSize.height);

  if (boundsButtonInventory.ContainsPoint(MousePositionF))
    engine.FillRectangle({100, 200, 255, 100}, boundsButtonInventory.x,
                         boundsButtonInventory.y, boundsButtonInventory.width,
                         boundsButtonInventory.height);
  else
    engine.FillRectangle({0, 150, 255, 100}, boundsButtonInventory.x,
                         boundsButtonInventory.y, boundsButtonInventory.width,
                         boundsButtonInventory.height);

  engine.DrawRectangle({255, 255, 255, 100}, boundsButtonInventory.x,
                       boundsButtonInventory.y, boundsButtonInventory.width,
                       boundsButtonInventory.height);
  engine.DrawString("Inventory [F2]", {255, 255, 255, 255},
                    boundsButtonInventory.x + boundsButtonInventory.width / 2,
                    boundsButtonInventory.y + boundsButtonInventory.height / 2,
                    true);

  if (boundsButtonCharacter.ContainsPoint(MousePositionF))
    engine.FillRectangle({100, 200, 255, 100}, boundsButtonCharacter.x,
                         boundsButtonCharacter.y, boundsButtonCharacter.width,
                         boundsButtonCharacter.height);
  else
    engine.FillRectangle({0, 150, 255, 100}, boundsButtonCharacter.x,
                         boundsButtonCharacter.y, boundsButtonCharacter.width,
                         boundsButtonCharacter.height);

  engine.DrawRectangle({255, 255, 255, 100}, boundsButtonCharacter.x,
                       boundsButtonCharacter.y, boundsButtonCharacter.width,
                       boundsButtonCharacter.height);
  engine.DrawString("Character [F1]", {255, 255, 255, 255},
                    boundsButtonCharacter.x + boundsButtonCharacter.width / 2,
                    boundsButtonCharacter.y + boundsButtonCharacter.height / 2,
                    true);

  if (boundsButtonSystem.ContainsPoint(MousePositionF))
    engine.FillRectangle({100, 200, 255, 100}, boundsButtonSystem.x,
                         boundsButtonSystem.y, boundsButtonSystem.width,
                         boundsButtonSystem.height);
  else
    engine.FillRectangle({0, 150, 255, 100}, boundsButtonSystem.x,
                         boundsButtonSystem.y, boundsButtonSystem.width,
                         boundsButtonSystem.height);

  engine.DrawRectangle({255, 255, 255, 100}, boundsButtonSystem.x,
                       boundsButtonSystem.y, boundsButtonSystem.width,
                       boundsButtonSystem.height);
  engine.DrawString("System [F3]", {255, 255, 255, 255},
                    boundsButtonSystem.x + boundsButtonSystem.width / 2,
                    boundsButtonSystem.y + boundsButtonSystem.height / 2, true);
  engine.FillRectangle({0, 150, 255, 20}, boundsTextBox.x, boundsTextBox.y,
                       boundsTextBox.width, boundsTextBox.height);
  engine.DrawRectangle({255, 255, 255, 100}, boundsTextBox.x, boundsTextBox.y,
                       boundsTextBox.width, boundsTextBox.height);

  auto TextBoxTextX = boundsTextBox.x + textBoxMargin;
  auto TextBoxTextY = boundsTextBox.y + textBoxMargin;

  engine.DrawString(textBoxText.at(0), {255, 255, 255, 255}, TextBoxTextX,
                    TextBoxTextY);

  for (auto &[Key, Window] : windows)
    Window->Render();
}

bool cGui::DoMouseDown(Uint8 mouseButton) {
  for (auto &[key, window] : windows) {
    auto clickedInWindow = window->DoMouseDown(mouseButton);

    if (clickedInWindow)
      return true;
  }

  auto mousePositionF = utilities.GetMousePositionF();

  if (boundsButtonInventory.ContainsPoint(mousePositionF)) {
    windows.at("Inventory")->visible = !windows.at("Inventory")->visible;

    return true;
  }

  auto mallIconSize = utilities.ConvertToFloat(buttonMallSize);

  auto mallIconBounds = cRectF {1.0f - mallIconSize.width, 0.0f, mallIconSize.width, mallIconSize.height};

  if (mallIconBounds.ContainsPoint(mousePositionF)) {
      windows.at("Mall")->visible = !windows.at("Mall")->visible;

      return true;
  }

  return false;
}

void cGui::DoMouseUp() {
  for (auto &[key, window] : windows)
    window->DoMouseUp();
}

}  // namespace Forradia
