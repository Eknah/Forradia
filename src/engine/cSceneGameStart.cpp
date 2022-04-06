// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cSceneGameStart.h"

namespace Forradia {

void cSceneGameStart::Update() {
    if (Engine.keyboardHandler.keysBeenFired->size() > 0)
      Engine.sceneManager.SwitchToScene(switchToSceneName);

    if (Engine.mouseHandler.GetLeftButtonBeenFired()
            || Engine.mouseHandler.GetRightButtonBeenFired())
        Engine.sceneManager.SwitchToScene(switchToSceneName);
  }

void cSceneGameStart::Render() {
    Engine.DrawImage(imageNameBackground, 0, 0, 1, 1);

    auto LogoSizeF = Engine.GetImageSizeF(imageNameLogo);

    Engine.DrawImage(imageNameLogo, 0.5f - LogoSizeF.width / 2.0f,
                     0.25f - LogoSizeF.height / 2.0f,
                     LogoSizeF.width,
                     LogoSizeF.height);
    Engine.DrawString(text, {255, 255, 255, 255}, 0.5f, 0.5f, true);
  }

}  // namespace Forradia
