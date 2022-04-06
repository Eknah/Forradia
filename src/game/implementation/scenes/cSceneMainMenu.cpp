// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cSceneMainMenu.h"
#include "../engine/cEngine.h"

namespace Forradia {

void cSceneMainMenu::Enter() {
    sceneButtons.clear();
    sceneButtons.push_back({{0.5f, 0.4f, 0.1f, 0.05f}, "Client"});
    sceneButtons.push_back({{0.5f, 0.47f, 0.1f, 0.05f}, "Server"});
}

void cSceneMainMenu::Update() {
  if (engine.keyboardHandler.keysBeenFired->size() > 0)
    engine.sceneManager.SwitchToScene("ScenePrimary");

  if (engine.mouseHandler.GetLeftButtonBeenFired()
          || engine.mouseHandler.GetRightButtonBeenFired())
      engine.sceneManager.SwitchToScene("ScenePrimary");
}

void cSceneMainMenu::Render() {
  engine.DrawImage("SceneGameStartBackground", 0, 0, 1, 1);

  auto CanvasSize = Utilities.GetCanvasSize();

  auto LogoSizeF = engine.GetImageSizeF("SceneForradiaLogo");

  engine.DrawImage("SceneForradiaLogo",
                   0.5f - LogoSizeF.width / 4.0f,
                   0.15f - LogoSizeF.height / 4.0f,
                   LogoSizeF.width/2,
                   LogoSizeF.height/2);

  for (auto& button : sceneButtons) {
    engine.FillRectangle(palette.wheat, button.bounds.x - button.bounds.width/2, button.bounds.y - button.bounds.height/2, button.bounds.width, button.bounds.height);
    engine.DrawString(button.text, palette.black, button.bounds.x, button.bounds.y, true);
  }
}

}  // namespace Forradia
