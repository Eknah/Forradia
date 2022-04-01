// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cSceneGameStart.h"

namespace Forradia {

void cSceneGameStart::Update() {
    if (Engine.KeyboardHandler.KeysBeenFired->size() > 0)
      Engine.SceneManager.SwitchToScene(SwitchToSceneName);

    if (Engine.MouseHandler.GetLeftButtonBeenFired()
            || Engine.MouseHandler.GetRightButtonBeenFired())
        Engine.SceneManager.SwitchToScene(SwitchToSceneName);
  }

void cSceneGameStart::Render() {
    Engine.DrawImage(ImageNameBackground, 0, 0, 1, 1);

    auto LogoSizeF = Engine.GetImageSizeF(ImageNameLogo);

    Engine.DrawImage(ImageNameLogo, 0.5f - LogoSizeF.Width / 2.0f,
                     0.25f - LogoSizeF.Height / 2.0f,
                     LogoSizeF.Width,
                     LogoSizeF.Height);
    Engine.DrawString(Text, {255, 255, 255, 255}, 0.5f, 0.5f, true);
  }

}  // namespace Forradia
