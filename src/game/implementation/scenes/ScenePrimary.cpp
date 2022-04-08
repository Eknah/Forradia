// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ScenePrimary.h"
#include "../engine/Engine.h"
#include "implementation/functionality/actor/modules/ModuleMovementData.h"

namespace Forradia {

void ScenePrimary::Enter() {
    gui.Initialize();
}

void ScenePrimary::Update() {
  auto &keys = e.keyboardHandler.keysBeingPressed;
  auto &player = e.GetPlayer();

  player.ResetForNewFrame();

  auto instruction = ModuleMovement::MovementInstruction();

  instruction.tryMoveForward = keys->count(SDLK_w);
  instruction.tryMoveRight = keys->count(SDLK_d);
  instruction.tryMoveBack = keys->count(SDLK_s);
  instruction.tryMoveLeft = keys->count(SDLK_a);

  player.GetModule<ModuleMovement>().instruction = instruction;

  if (instruction.tryMoveForward || instruction.tryMoveRight ||
      instruction.tryMoveBack || instruction.tryMoveLeft) {
    *player.GetModule<ModuleMovementData>().facingAngle = camera.lookingAngle;
    player.GetModule<ModuleMovementData>().moveDestination = {-1, -1};
  }

  auto turnRight = keys->count(SDLK_e);
  auto turnLeft = keys->count(SDLK_q);

  if (turnRight) {
    camera.Update(GetId("Right"), *e.mouseHandler.wheelAmount);
    player.GetModule<ModuleMovement>().UpdateRotation(camera.lookingAngle);
  } else if (turnLeft) {
    camera.Update(GetId("Left"), *e.mouseHandler.wheelAmount);
    player.GetModule<ModuleMovement>().UpdateRotation(camera.lookingAngle);
  } else {
    camera.Update(0, *e.mouseHandler.wheelAmount);
  }

  if (e.keyboardHandler.keysBeenFired->count(SDLK_F2))
    gui.windows.at("Inventory")->visible =
        !gui.windows.at("Inventory")->visible;

  camera.UpdateCameraMovement();

  if (e.mouseHandler.rightButtonDown)
    *player.GetModule<ModuleMovementData>().facingAngle = camera.lookingAngle;

  if (e.keyboardHandler.keysBeenFired->count(SDLK_SPACE) > 0)
    e.GetPlayer().GetModule<ModuleJumping>().Jump();

  if (e.mouseHandler.rightButtonDown)
    e.customCursor.cursorType = CursorTypes::Hidden;

  player.Update();
  mobsEngine.Update();
  gui.Update();
}

void ScenePrimary::Render() {
  gameWorldRenderer.Render();
  gui.Render();
}

void ScenePrimary::DoMouseDown(Uint8 mouseButton) {
  if (e.GetPlayer().GetModule<ModuleObjectUsage>().objectBeingUsed !=
      nullptr) {
    auto hovered = camera.GetHoveredTile();

    if (e.GetCurrentMapArea().tiles[hovered.x][hovered.y].objects.size() >
        0)
      e.GetPlayer().GetModule<ModuleObjectUsage>().objectBeingUsed->UseOn(
          e.GetCurrentMapArea().tiles[hovered.x][hovered.y].objects.at(
              e.GetCurrentMapArea()
                  .tiles[hovered.x][hovered.y]
                  .objects.size() -
              1));

    e.GetPlayer().GetModule<ModuleObjectUsage>().objectBeingUsed
            = nullptr;

    return;
  }

  auto clickedInGui = gui.DoMouseDown(mouseButton);

  if (clickedInGui)
    return;

  switch (mouseButton) {
  case SDL_BUTTON_LEFT: {
    e.GetPlayer().GetModule<ModuleMovementData>().moveDestination = {
        camera.GetHoveredTile().x + 0.5f, camera.GetHoveredTile().y + 0.5f};
    break;
  }
  case SDL_BUTTON_RIGHT: {
    break;
  }
  }
}

void ScenePrimary::DoMouseUp(Uint8 MouseButton) {
    gui.DoMouseUp();
}

}  // namespace Forradia
