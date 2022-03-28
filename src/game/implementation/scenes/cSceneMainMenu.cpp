// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cSceneMainMenu.h"
#include "../engine/cEngine.h"
#include "CommonExternal.h"

namespace Forradia {

void cSceneMainMenu::Update() {
  if (Engine.KeyboardHandler.KeysBeenFired->size() > 0)
    Engine.SceneManager.SwitchToScene("ScenePrimary");

  if (Engine.MouseHandler.GetLeftButtonBeenFired() || Engine.MouseHandler.GetRightButtonBeenFired())
      Engine.SceneManager.SwitchToScene("ScenePrimary");
}

void cSceneMainMenu::Render() {
  Engine.DrawImage("SceneGameStartBackground", 0, 0, 1, 1);

  auto CanvasSize = Utilities.GetCanvasSize();

  auto LogoSizeF = Engine.GetImageSizeF("SceneForradiaLogo");

  Engine.DrawImage("SceneForradiaLogo", 0.5f - LogoSizeF.Width / 4.0f,
                   0.15f - LogoSizeF.Height / 4.0f, LogoSizeF.Width/2, LogoSizeF.Height/2);
}

}  // namespace Forradia
