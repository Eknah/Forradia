// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cScenePrimary.h"
#include "../engine/cEngine.h"
#include "implementation/functionality/actor/modules/cModuleMovementData.h"

namespace Forradia {

void cScenePrimary::Enter() { Gui.Initialize(); }

void cScenePrimary::Update() {
  auto &Keys = Engine.keyboardHandler.KeysBeingPressed;
  auto &Player = Engine.GetPlayer();

  Player.ResetForNewFrame();

  auto Instruction = cModuleMovement::MovementInstruction();

  Instruction.TryMoveForward = Keys->count(SDLK_w);
  Instruction.TryMoveRight = Keys->count(SDLK_d);
  Instruction.TryMoveBack = Keys->count(SDLK_s);
  Instruction.TryMoveLeft = Keys->count(SDLK_a);

  Player.GetModule<cModuleMovement>().Instruction = Instruction;

  if (Instruction.TryMoveForward || Instruction.TryMoveRight ||
      Instruction.TryMoveBack || Instruction.TryMoveLeft) {
    *Player.GetModule<cModuleMovementData>().FacingAngle = Camera.LookingAngle;
    Player.GetModule<cModuleMovementData>().MoveDestination = {-1, -1};
  }

  auto TurnRight = Keys->count(SDLK_e);
  auto TurnLeft = Keys->count(SDLK_q);

  if (TurnRight) {
    Camera.Update(GetId("Right"), *Engine.mouseHandler.wheelAmount);
    Player.GetModule<cModuleMovement>().UpdateRotation(Camera.LookingAngle);
  } else if (TurnLeft) {
    Camera.Update(GetId("Left"), *Engine.mouseHandler.wheelAmount);
    Player.GetModule<cModuleMovement>().UpdateRotation(Camera.LookingAngle);
  } else {
    Camera.Update(0, *Engine.mouseHandler.wheelAmount);
  }

  if (Engine.keyboardHandler.KeysBeenFired->count(SDLK_F2))
    Gui.Windows.at("Inventory")->Visible =
        !Gui.Windows.at("Inventory")->Visible;

  Camera.UpdateCameraMovement();

  if (Engine.mouseHandler.rightButtonDown)
    *Player.GetModule<cModuleMovementData>().FacingAngle = Camera.LookingAngle;

  if (Engine.keyboardHandler.KeysBeenFired->count(SDLK_SPACE) > 0)
    Engine.GetPlayer().GetModule<cModuleJumping>().Jump();

  if (Engine.mouseHandler.rightButtonDown)
    Engine.customCursor.cursorType = eCursorTypes::Hidden;

  Player.Update();
  MobsEngine.Update();
  Gui.Update();
}

void cScenePrimary::Render() {
  GameWorldRenderer.Render();
  Gui.Render();
}

void cScenePrimary::DoMouseDown(Uint8 MouseButton) {
  if (Engine.GetPlayer().GetModule<cModuleObjectUsage>().ObjectBeingUsed !=
      nullptr) {
    auto Hovered = Camera.GetHoveredTile();

    if (Engine.GetCurrentMapArea().tiles[Hovered.x][Hovered.y].objects.size() >
        0)
      Engine.GetPlayer().GetModule<cModuleObjectUsage>().ObjectBeingUsed->UseOn(
          Engine.GetCurrentMapArea().tiles[Hovered.x][Hovered.y].objects.at(
              Engine.GetCurrentMapArea()
                  .tiles[Hovered.x][Hovered.y]
                  .objects.size() -
              1));

    Engine.GetPlayer().GetModule<cModuleObjectUsage>().ObjectBeingUsed
            = nullptr;

    return;
  }

  auto ClickedInGui = Gui.DoMouseDown(MouseButton);

  if (ClickedInGui)
    return;

  switch (MouseButton) {
  case SDL_BUTTON_LEFT: {
    Engine.GetPlayer().GetModule<cModuleMovementData>().MoveDestination = {
        Camera.GetHoveredTile().x + 0.5f, Camera.GetHoveredTile().y + 0.5f};
    break;
  }
  case SDL_BUTTON_RIGHT: {
    break;
  }
  }
}

void cScenePrimary::DoMouseUp(Uint8 MouseButton) { Gui.DoMouseUp(); }

}  // namespace Forradia
