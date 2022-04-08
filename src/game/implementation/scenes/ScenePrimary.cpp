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
  auto &keys = engine.keyboardHandler.keysBeingPressed;
  auto &player = engine.GetPlayer();

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
    camera.Update(GetId("Right"), *engine.mouseHandler.wheelAmount);
    player.GetModule<ModuleMovement>().UpdateRotation(camera.lookingAngle);
  } else if (turnLeft) {
    camera.Update(GetId("Left"), *engine.mouseHandler.wheelAmount);
    player.GetModule<ModuleMovement>().UpdateRotation(camera.lookingAngle);
  } else {
    camera.Update(0, *engine.mouseHandler.wheelAmount);
  }

  if (engine.keyboardHandler.keysBeenFired->count(SDLK_F2))
    gui.windows.at("Inventory")->visible =
        !gui.windows.at("Inventory")->visible;

  camera.UpdateCameraMovement();

  if (engine.mouseHandler.rightButtonDown)
    *player.GetModule<ModuleMovementData>().facingAngle = camera.lookingAngle;

  if (engine.keyboardHandler.keysBeenFired->count(SDLK_SPACE) > 0)
    engine.GetPlayer().GetModule<ModuleJumping>().Jump();

  if (engine.mouseHandler.rightButtonDown)
    engine.customCursor.cursorType = CursorTypes::Hidden;

  player.Update();
  mobsEngine.Update();
  gui.Update();
}

void ScenePrimary::Render() {
  gameWorldRenderer.Render();
  gui.Render();
}

void ScenePrimary::DoMouseDown(Uint8 mouseButton) {
  if (engine.GetPlayer().GetModule<ModuleObjectUsage>().objectBeingUsed !=
      nullptr) {
    auto hovered = camera.GetHoveredTile();

    if (engine.GetCurrentMapArea().tiles[hovered.x][hovered.y].objects.size() >
        0)
      engine.GetPlayer().GetModule<ModuleObjectUsage>().objectBeingUsed->UseOn(
          engine.GetCurrentMapArea().tiles[hovered.x][hovered.y].objects.at(
              engine.GetCurrentMapArea()
                  .tiles[hovered.x][hovered.y]
                  .objects.size() -
              1));

    engine.GetPlayer().GetModule<ModuleObjectUsage>().objectBeingUsed
            = nullptr;

    return;
  }

  auto clickedInGui = gui.DoMouseDown(mouseButton);

  if (clickedInGui)
    return;

  switch (mouseButton) {
  case SDL_BUTTON_LEFT: {
    engine.GetPlayer().GetModule<ModuleMovementData>().moveDestination = {
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
