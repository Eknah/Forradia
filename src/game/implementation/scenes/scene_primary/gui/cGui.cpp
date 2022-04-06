// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "cGui.h"
#include "../engine/cEngine.h"
#include "cGuiWindowInventory.h"
#include "cGuiWindowMall.h"

namespace Forradia {

void cGui::Initialize() {
  Windows.clear();
  Windows.insert(
      {"Inventory", std::make_unique<cGuiWindowInventory>(
                        Engine, "Inventory", cRectF{0.1f, 0.1f, 0.2f, 0.7f})});
  Windows.insert(
      {"Mall", std::make_unique<cGuiWindowMall>(
                        Engine, "Mall", cRectF{0.2f, 0.1f, 0.7f, 0.6f})});
}

void cGui::Update() {
  auto MousePositionF = Utilities.GetMousePositionF();

  if (BoundsButtonInventory.ContainsPoint(MousePositionF))
    Engine.customCursor.cursorType = eCursorTypes::Hovering;

  if (BoundsButtonCharacter.ContainsPoint(MousePositionF))
    Engine.customCursor.cursorType = eCursorTypes::Hovering;

  if (BoundsButtonSystem.ContainsPoint(MousePositionF))
    Engine.customCursor.cursorType = eCursorTypes::Hovering;

  auto mallIconSize = Utilities.ConvertToFloat(ButtonMallSize);

  auto mallIconBounds = cRectF {1.0f - mallIconSize.width, 0.0f, mallIconSize.width, mallIconSize.height};

  if (mallIconBounds.ContainsPoint(MousePositionF))
    Engine.customCursor.cursorType = eCursorTypes::Hovering;

  for (auto &[Key, Window] : Windows)
    Window->Update();
}

void cGui::Render() {
  GuiMinimap.Render();

  auto MousePositionF = Utilities.GetMousePositionF();



  auto mallIconSize = Utilities.ConvertToFloat(ButtonMallSize);

  auto mallIconBounds = cRectF {1.0f - mallIconSize.width, 0.0f, mallIconSize.width, mallIconSize.height};

  if (mallIconBounds.ContainsPoint(MousePositionF))
    Engine.DrawImage("GuiIconMallHovered", 1.0f - mallIconSize.width, 0.0f, mallIconSize.width, mallIconSize.height);
  else
      Engine.DrawImage("GuiIconMall", 1.0f - mallIconSize.width, 0.0f, mallIconSize.width, mallIconSize.height);

  if (BoundsButtonInventory.ContainsPoint(MousePositionF))
    Engine.FillRectangle({100, 200, 255, 100}, BoundsButtonInventory.x,
                         BoundsButtonInventory.y, BoundsButtonInventory.width,
                         BoundsButtonInventory.height);
  else
    Engine.FillRectangle({0, 150, 255, 100}, BoundsButtonInventory.x,
                         BoundsButtonInventory.y, BoundsButtonInventory.width,
                         BoundsButtonInventory.height);

  Engine.DrawRectangle({255, 255, 255, 100}, BoundsButtonInventory.x,
                       BoundsButtonInventory.y, BoundsButtonInventory.width,
                       BoundsButtonInventory.height);
  Engine.DrawString("Inventory [F2]", {255, 255, 255, 255},
                    BoundsButtonInventory.x + BoundsButtonInventory.width / 2,
                    BoundsButtonInventory.y + BoundsButtonInventory.height / 2,
                    true);

  if (BoundsButtonCharacter.ContainsPoint(MousePositionF))
    Engine.FillRectangle({100, 200, 255, 100}, BoundsButtonCharacter.x,
                         BoundsButtonCharacter.y, BoundsButtonCharacter.width,
                         BoundsButtonCharacter.height);
  else
    Engine.FillRectangle({0, 150, 255, 100}, BoundsButtonCharacter.x,
                         BoundsButtonCharacter.y, BoundsButtonCharacter.width,
                         BoundsButtonCharacter.height);

  Engine.DrawRectangle({255, 255, 255, 100}, BoundsButtonCharacter.x,
                       BoundsButtonCharacter.y, BoundsButtonCharacter.width,
                       BoundsButtonCharacter.height);
  Engine.DrawString("Character [F1]", {255, 255, 255, 255},
                    BoundsButtonCharacter.x + BoundsButtonCharacter.width / 2,
                    BoundsButtonCharacter.y + BoundsButtonCharacter.height / 2,
                    true);

  if (BoundsButtonSystem.ContainsPoint(MousePositionF))
    Engine.FillRectangle({100, 200, 255, 100}, BoundsButtonSystem.x,
                         BoundsButtonSystem.y, BoundsButtonSystem.width,
                         BoundsButtonSystem.height);
  else
    Engine.FillRectangle({0, 150, 255, 100}, BoundsButtonSystem.x,
                         BoundsButtonSystem.y, BoundsButtonSystem.width,
                         BoundsButtonSystem.height);

  Engine.DrawRectangle({255, 255, 255, 100}, BoundsButtonSystem.x,
                       BoundsButtonSystem.y, BoundsButtonSystem.width,
                       BoundsButtonSystem.height);
  Engine.DrawString("System [F3]", {255, 255, 255, 255},
                    BoundsButtonSystem.x + BoundsButtonSystem.width / 2,
                    BoundsButtonSystem.y + BoundsButtonSystem.height / 2, true);
  Engine.FillRectangle({0, 150, 255, 100}, BoundsTextBox.x, BoundsTextBox.y,
                       BoundsTextBox.width, BoundsTextBox.height);
  Engine.DrawRectangle({255, 255, 255, 100}, BoundsTextBox.x, BoundsTextBox.y,
                       BoundsTextBox.width, BoundsTextBox.height);

  auto TextBoxTextX = BoundsTextBox.x + TextBoxMargin;
  auto TextBoxTextY = BoundsTextBox.y + TextBoxMargin;

  Engine.DrawString(TextBoxText.at(0), {255, 255, 255, 255}, TextBoxTextX,
                    TextBoxTextY);

  for (auto &[Key, Window] : Windows)
    Window->Render();
}

bool cGui::DoMouseDown(Uint8 MouseButton) {
  for (auto &[Key, Window] : Windows) {
    auto ClickedInWindow = Window->DoMouseDown(MouseButton);

    if (ClickedInWindow)
      return true;
  }

  auto MousePositionF = Utilities.GetMousePositionF();

  if (BoundsButtonInventory.ContainsPoint(MousePositionF)) {
    Windows.at("Inventory")->Visible = !Windows.at("Inventory")->Visible;

    return true;
  }

  auto mallIconSize = Utilities.ConvertToFloat(ButtonMallSize);

  auto mallIconBounds = cRectF {1.0f - mallIconSize.width, 0.0f, mallIconSize.width, mallIconSize.height};

  if (mallIconBounds.ContainsPoint(MousePositionF)) {
      Windows.at("Mall")->Visible = !Windows.at("Mall")->Visible;

      return true;
  }

  return false;
}

void cGui::DoMouseUp() {
  for (auto &[Key, Window] : Windows)
    Window->DoMouseUp();
}

}  // namespace Forradia
