// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "SceneGameStart.h"

namespace Forradia
{

    void SceneGameStart::Render()
    {
        e.DrawImage(imageNameBackground, 0, 0, 1, 1);

        auto logoSizeF = e.GetImageSizeF(imageNameLogo);

        e.DrawImage(imageNameLogo, 0.5f - logoSizeF.w / 2.0f,
            0.25f - logoSizeF.h / 2.0f,
            logoSizeF.w,
            logoSizeF.h);
        e.DrawString(text, SDL_Color { 255, 255, 255, 255 }, 0.5f, 0.5f, true);

    }

    void SceneGameStart::MouseDown(Uint8 mouseButton)
    {
        e.sceneManager.SwitchToScene(switchToSceneName);
    }

    void SceneGameStart::KeyDown(SDL_Keycode key)
    {
        e.sceneManager.SwitchToScene(switchToSceneName);
    }

}  // namespace Forradia
