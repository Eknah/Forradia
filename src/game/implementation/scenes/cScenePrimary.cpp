// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cScenePrimary.h"
#include "../engine/cEngine.h"
#include "implementation/functionality/actor/modules/cModuleMovementData.h"

namespace Forradia {

void cScenePrimary::Enter() {
    Gui.Initialize();
}

void cScenePrimary::Update() {
  auto &Keys = engine.keyboardHandler.keysBeingPressed;
  auto &Player = engine.GetPlayer();

  Player.ResetForNewFrame();

  auto Instruction = cModuleMovement::MovementInstruction();

  Instruction.tryMoveForward = Keys->count(SDLK_w);
  Instruction.tryMoveRight = Keys->count(SDLK_d);
  Instruction.tryMoveBack = Keys->count(SDLK_s);
  Instruction.tryMoveLeft = Keys->count(SDLK_a);

  Player.GetModule<cModuleMovement>().instruction = Instruction;

  if (Instruction.tryMoveForward || Instruction.tryMoveRight ||
      Instruction.tryMoveBack || Instruction.tryMoveLeft) {
    *Player.GetModule<cModuleMovementData>().facingAngle = Camera.LookingAngle;
    Player.GetModule<cModuleMovementData>().moveDestination = {-1, -1};
  }

  auto TurnRight = Keys->count(SDLK_e);
  auto TurnLeft = Keys->count(SDLK_q);

  if (TurnRight) {
    Camera.Update(GetId("Right"), *engine.mouseHandler.wheelAmount);
    Player.GetModule<cModuleMovement>().UpdateRotation(Camera.LookingAngle);
  } else if (TurnLeft) {
    Camera.Update(GetId("Left"), *engine.mouseHandler.wheelAmount);
    Player.GetModule<cModuleMovement>().UpdateRotation(Camera.LookingAngle);
  } else {
    Camera.Update(0, *engine.mouseHandler.wheelAmount);
  }

  if (engine.keyboardHandler.keysBeenFired->count(SDLK_F2))
    Gui.Windows.at("Inventory")->visible =
        !Gui.Windows.at("Inventory")->visible;

  Camera.UpdateCameraMovement();

  if (engine.mouseHandler.rightButtonDown)
    *Player.GetModule<cModuleMovementData>().facingAngle = Camera.LookingAngle;

  if (engine.keyboardHandler.keysBeenFired->count(SDLK_SPACE) > 0)
    engine.GetPlayer().GetModule<cModuleJumping>().Jump();

  if (engine.mouseHandler.rightButtonDown)
    engine.customCursor.cursorType = eCursorTypes::Hidden;

  Player.Update();
  MobsEngine.Update();
  Gui.Update();
}

void cScenePrimary::Render() {
  GameWorldRenderer.Render();
  Gui.Render();
}

void cScenePrimary::DoMouseDown(Uint8 MouseButton) {
  if (engine.GetPlayer().GetModule<cModuleObjectUsage>().objectBeingUsed !=
      nullptr) {
    auto Hovered = Camera.GetHoveredTile();

    if (engine.GetCurrentMapArea().tiles[Hovered.x][Hovered.y].objects.size() >
        0)
      engine.GetPlayer().GetModule<cModuleObjectUsage>().objectBeingUsed->UseOn(
          engine.GetCurrentMapArea().tiles[Hovered.x][Hovered.y].objects.at(
              engine.GetCurrentMapArea()
                  .tiles[Hovered.x][Hovered.y]
                  .objects.size() -
              1));

    engine.GetPlayer().GetModule<cModuleObjectUsage>().objectBeingUsed
            = nullptr;

    return;
  }

  auto ClickedInGui = Gui.DoMouseDown(MouseButton);

  if (ClickedInGui)
    return;

  switch (MouseButton) {
  case SDL_BUTTON_LEFT: {
    engine.GetPlayer().GetModule<cModuleMovementData>().moveDestination = {
        Camera.GetHoveredTile().x + 0.5f, Camera.GetHoveredTile().y + 0.5f};
    break;
  }
  case SDL_BUTTON_RIGHT: {
    break;
  }
  }
}

void cScenePrimary::DoMouseUp(Uint8 MouseButton) {
    Gui.DoMouseUp();
}

}  // namespace Forradia
