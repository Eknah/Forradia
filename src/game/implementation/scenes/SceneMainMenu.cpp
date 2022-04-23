// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "SceneMainMenu.h"
#include "../engine/Engine.h"

namespace Forradia
{

    void SceneMainMenu::Enter()
    {
        sceneButtons.clear();
        sceneButtons.push_back({ {0.5f, 0.4f, 0.1f, 0.05f}, "New Game" });
        sceneButtons.push_back({ {0.5f, 0.47f, 0.1f, 0.05f}, "Exit" });
    }

    void SceneMainMenu::Render()
    {
        using namespace Palette;

        _ DrawImage("SceneGameStartBackground", 0, 0, 1, 1);

        auto canvasSz = utils.GetCanvasSize();
        auto logoSzF = _ GetImageSizeF("SceneForradiaLogo");

        _ DrawImage
        (
            "SceneForradiaLogo",
            0.5f - logoSzF.w / 4.0f,
            0.15f - logoSzF.h / 4.0f,
            logoSzF.w / 2,
            logoSzF.h / 2
        );

        for (auto& button : sceneButtons)
        {
            _ FillRect(Wheat, button.bounds.x - button.bounds.w / 2, button.bounds.y - button.bounds.h / 2, button.bounds.w, button.bounds.h);
            _ DrawString(button.text, Black, button.bounds.x, button.bounds.y, true);
        }
    }

    void SceneMainMenu::MouseDown(Uint8 mouseButton)
    {
        _ sceneManager.SwitchToScene("ScenePrimary");
    }
    
    void SceneMainMenu::KeyDown(SDL_Keycode key)
    {
        _ sceneManager.SwitchToScene("ScenePrimary");
    }

}  // namespace Forradia
