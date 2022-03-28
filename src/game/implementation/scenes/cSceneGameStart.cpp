// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cSceneGameStart.h"
#include "../engine/cEngine.h"
#include "CommonExternal.h"

namespace Forradia {

void cSceneGameStart::Update() {
  if (Engine.KeyboardHandler.KeysBeenFired->size() > 0)
    Engine.SceneManager.SwitchToScene("SceneMainMenu");

  if (Engine.MouseHandler.GetLeftButtonBeenFired() || Engine.MouseHandler.GetRightButtonBeenFired())
      Engine.SceneManager.SwitchToScene("SceneMainMenu");
}

void cSceneGameStart::Render() {
  Engine.DrawImage("SceneGameStartBackground", 0, 0, 1, 1);

  auto LogoSizeF = Engine.GetImageSizeF("SceneForradiaLogo");

  Engine.DrawImage("SceneForradiaLogo", 0.5f - LogoSizeF.Width / 2.0f,
                   0.25f - LogoSizeF.Height / 2.0f, LogoSizeF.Width, LogoSizeF.Height);
  Engine.DrawString("Press to start", {255, 255, 255, 255}, 0.5f, 0.5f, true);
}

}  // namespace Forradia
