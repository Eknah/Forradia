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
  if (Engine.keyboardHandler.KeysBeenFired->size() > 0)
    Engine.sceneManager.SwitchToScene("ScenePrimary");

  if (Engine.mouseHandler.GetLeftButtonBeenFired()
          || Engine.mouseHandler.GetRightButtonBeenFired())
      Engine.sceneManager.SwitchToScene("ScenePrimary");
}

void cSceneMainMenu::Render() {
  Engine.DrawImage("SceneGameStartBackground", 0, 0, 1, 1);

  auto CanvasSize = Utilities.GetCanvasSize();

  auto LogoSizeF = Engine.GetImageSizeF("SceneForradiaLogo");

  Engine.DrawImage("SceneForradiaLogo",
                   0.5f - LogoSizeF.width / 4.0f,
                   0.15f - LogoSizeF.height / 4.0f,
                   LogoSizeF.width/2,
                   LogoSizeF.height/2);

  for (auto& button : sceneButtons) {
    Engine.FillRectangle(palette.wheat, button.Bounds.x - button.Bounds.width/2, button.Bounds.y - button.Bounds.height/2, button.Bounds.width, button.Bounds.height);
    Engine.DrawString(button.Text, palette.black, button.Bounds.x, button.Bounds.y, true);
  }
}

}  // namespace Forradia
