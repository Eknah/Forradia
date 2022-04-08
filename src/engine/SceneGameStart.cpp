// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "SceneGameStart.h"

namespace Forradia {

void SceneGameStart::Update() {
    if (engine.keyboardHandler.keysBeenFired->size() > 0)
      engine.sceneManager.SwitchToScene(switchToSceneName);

    if (engine.mouseHandler.GetLeftButtonBeenFired()
            || engine.mouseHandler.GetRightButtonBeenFired())
        engine.sceneManager.SwitchToScene(switchToSceneName);
  }

void SceneGameStart::Render() {
    engine.DrawImage(imageNameBackground, 0, 0, 1, 1);

    auto logoSizeF = engine.GetImageSizeF(imageNameLogo);

    engine.DrawImage(imageNameLogo, 0.5f - logoSizeF.width / 2.0f,
                     0.25f - logoSizeF.height / 2.0f,
                     logoSizeF.width,
                     logoSizeF.height);
    engine.DrawString(text, {255, 255, 255, 255}, 0.5f, 0.5f, true);
  }

}  // namespace Forradia
