// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cSceneGameStart.h"

namespace Forradia {

void cSceneGameStart::Update() {
    if (engine.keyboardHandler.keysBeenFired->size() > 0)
      engine.sceneManager.SwitchToScene(switchToSceneName);

    if (engine.mouseHandler.GetLeftButtonBeenFired()
            || engine.mouseHandler.GetRightButtonBeenFired())
        engine.sceneManager.SwitchToScene(switchToSceneName);
  }

void cSceneGameStart::Render() {
    engine.DrawImage(imageNameBackground, 0, 0, 1, 1);

    auto LogoSizeF = engine.GetImageSizeF(imageNameLogo);

    engine.DrawImage(imageNameLogo, 0.5f - LogoSizeF.width / 2.0f,
                     0.25f - LogoSizeF.height / 2.0f,
                     LogoSizeF.width,
                     LogoSizeF.height);
    engine.DrawString(text, {255, 255, 255, 255}, 0.5f, 0.5f, true);
  }

}  // namespace Forradia
