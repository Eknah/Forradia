// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "SceneMainMenu.h"
#include "../engine/Engine.h"

namespace Forradia {

void SceneMainMenu::Enter() {
    sceneButtons.clear();
    sceneButtons.push_back({{0.5f, 0.4f, 0.1f, 0.05f}, "Client"});
    sceneButtons.push_back({{0.5f, 0.47f, 0.1f, 0.05f}, "Server"});
}

void SceneMainMenu::Update() {
  if (engine.keyboardHandler.keysBeenFired->size() > 0)
    engine.sceneManager.SwitchToScene("ScenePrimary");

  if (engine.mouseHandler.GetLeftButtonBeenFired()
          || engine.mouseHandler.GetRightButtonBeenFired())
      engine.sceneManager.SwitchToScene("ScenePrimary");
}

void SceneMainMenu::Render() {
  engine.DrawImage("SceneGameStartBackground", 0, 0, 1, 1);

  auto canvasSize = utilities.GetCanvasSize();

  auto logoSizeF = engine.GetImageSizeF("SceneForradiaLogo");

  engine.DrawImage("SceneForradiaLogo",
                   0.5f - logoSizeF.width / 4.0f,
                   0.15f - logoSizeF.height / 4.0f,
                   logoSizeF.width/2,
                   logoSizeF.height/2);

  for (auto& button : sceneButtons) {
    engine.FillRectangle(palette.wheat, button.bounds.x - button.bounds.width/2, button.bounds.y - button.bounds.height/2, button.bounds.width, button.bounds.height);
    engine.DrawString(button.text, palette.black, button.bounds.x, button.bounds.y, true);
  }
}

}  // namespace Forradia
