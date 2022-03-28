// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cGui.h"
#include "../engine/cEngine.h"
#include "cGuiWindowInventory.h"

namespace Forradia {

void cGui::Initialize() {
  Windows.clear();
  Windows.insert(
      {"Inventory", std::make_unique<cGuiWindowInventory>(
                        Engine, "Inventory", cRectF{0.1f, 0.1f, 0.2f, 0.7f})});
}

void cGui::Update() {
  auto MousePositionF = Utilities.GetMousePositionF();

  if (BoundsButtonInventory.ContainsPoint(MousePositionF))
    Engine.CustomCursor.CursorType = eCursorTypes::Hovering;

  if (BoundsButtonCharacter.ContainsPoint(MousePositionF))
    Engine.CustomCursor.CursorType = eCursorTypes::Hovering;

  if (BoundsButtonSystem.ContainsPoint(MousePositionF))
    Engine.CustomCursor.CursorType = eCursorTypes::Hovering;

  for (auto &[Key, Window] : Windows)
    Window->Update();
}

void cGui::Render() {
  GuiMinimap.Render();

  auto MousePositionF = Utilities.GetMousePositionF();

  if (BoundsButtonInventory.ContainsPoint(MousePositionF))
    Engine.FillRectangle({100, 200, 255, 100}, BoundsButtonInventory.X,
                         BoundsButtonInventory.Y, BoundsButtonInventory.Width,
                         BoundsButtonInventory.Height);
  else
    Engine.FillRectangle({0, 150, 255, 100}, BoundsButtonInventory.X,
                         BoundsButtonInventory.Y, BoundsButtonInventory.Width,
                         BoundsButtonInventory.Height);

  Engine.DrawRectangle({255, 255, 255, 100}, BoundsButtonInventory.X,
                       BoundsButtonInventory.Y, BoundsButtonInventory.Width,
                       BoundsButtonInventory.Height);
  Engine.DrawString("Inventory [F2]", {255, 255, 255, 255},
                    BoundsButtonInventory.X + BoundsButtonInventory.Width / 2,
                    BoundsButtonInventory.Y + BoundsButtonInventory.Height / 2,
                    true);

  if (BoundsButtonCharacter.ContainsPoint(MousePositionF))
    Engine.FillRectangle({100, 200, 255, 100}, BoundsButtonCharacter.X,
                         BoundsButtonCharacter.Y, BoundsButtonCharacter.Width,
                         BoundsButtonCharacter.Height);
  else
    Engine.FillRectangle({0, 150, 255, 100}, BoundsButtonCharacter.X,
                         BoundsButtonCharacter.Y, BoundsButtonCharacter.Width,
                         BoundsButtonCharacter.Height);

  Engine.DrawRectangle({255, 255, 255, 100}, BoundsButtonCharacter.X,
                       BoundsButtonCharacter.Y, BoundsButtonCharacter.Width,
                       BoundsButtonCharacter.Height);
  Engine.DrawString("Character [F1]", {255, 255, 255, 255},
                    BoundsButtonCharacter.X + BoundsButtonCharacter.Width / 2,
                    BoundsButtonCharacter.Y + BoundsButtonCharacter.Height / 2,
                    true);

  if (BoundsButtonSystem.ContainsPoint(MousePositionF))
    Engine.FillRectangle({100, 200, 255, 100}, BoundsButtonSystem.X,
                         BoundsButtonSystem.Y, BoundsButtonSystem.Width,
                         BoundsButtonSystem.Height);
  else
    Engine.FillRectangle({0, 150, 255, 100}, BoundsButtonSystem.X,
                         BoundsButtonSystem.Y, BoundsButtonSystem.Width,
                         BoundsButtonSystem.Height);

  Engine.DrawRectangle({255, 255, 255, 100}, BoundsButtonSystem.X,
                       BoundsButtonSystem.Y, BoundsButtonSystem.Width,
                       BoundsButtonSystem.Height);
  Engine.DrawString("System [F3]", {255, 255, 255, 255},
                    BoundsButtonSystem.X + BoundsButtonSystem.Width / 2,
                    BoundsButtonSystem.Y + BoundsButtonSystem.Height / 2, true);
  Engine.FillRectangle({0, 150, 255, 100}, BoundsTextBox.X, BoundsTextBox.Y,
                       BoundsTextBox.Width, BoundsTextBox.Height);
  Engine.DrawRectangle({255, 255, 255, 100}, BoundsTextBox.X, BoundsTextBox.Y,
                       BoundsTextBox.Width, BoundsTextBox.Height);

  auto TextBoxTextX = BoundsTextBox.X + TextBoxMargin;
  auto TextBoxTextY = BoundsTextBox.Y + TextBoxMargin;

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

  return false;
}

void cGui::DoMouseUp() {
  for (auto &[Key, Window] : Windows)
    Window->DoMouseUp();
}

} // namespace Forradia
