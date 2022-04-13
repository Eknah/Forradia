// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "SceneGameStart.h"

namespace Forradia
{

    void SceneGameStart::Update()
    {
        if (e.keyboardHandler.keysBeenFired->size() > 0)
            e.sceneManager.SwitchToScene(switchToSceneName);

        if (e.mouseHandler.GetLeftButtonBeenFired()
            || e.mouseHandler.GetRightButtonBeenFired())
            e.sceneManager.SwitchToScene(switchToSceneName);
    }

    void SceneGameStart::Render()
    {
        e.DrawImage(imageNameBackground, 0, 0, 1, 1);

        auto logoSizeF = e.GetImageSizeF(imageNameLogo);

        e.DrawImage(imageNameLogo, 0.5f - logoSizeF.width / 2.0f,
            0.25f - logoSizeF.height / 2.0f,
            logoSizeF.width,
            logoSizeF.height);
        e.DrawString(text, { 255, 255, 255, 255 }, 0.5f, 0.5f, true);
    }

}  // namespace Forradia
