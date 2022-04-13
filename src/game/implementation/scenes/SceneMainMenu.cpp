// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "SceneMainMenu.h"
#include "../engine/Engine.h"

namespace Forradia
{

    void SceneMainMenu::Enter()
    {
        sceneButtons.clear();
        sceneButtons.push_back({ {0.5f, 0.4f, 0.1f, 0.05f}, "Client" });
        sceneButtons.push_back({ {0.5f, 0.47f, 0.1f, 0.05f}, "Server" });
    }

    void SceneMainMenu::Update()
    {
        if (e.keyboardHandler.keysBeenFired->size() > 0)
            e.sceneManager.SwitchToScene("ScenePrimary");

        if (e.mouseHandler.GetLeftButtonBeenFired()
            || e.mouseHandler.GetRightButtonBeenFired())
            e.sceneManager.SwitchToScene("ScenePrimary");
    }

    void SceneMainMenu::Render()
    {
        e.DrawImage("SceneGameStartBackground", 0, 0, 1, 1);

        auto canvasSize = utils.GetCanvasSize();

        auto logoSizeF = e.GetImageSizeF("SceneForradiaLogo");

        e.DrawImage("SceneForradiaLogo",
            0.5f - logoSizeF.width / 4.0f,
            0.15f - logoSizeF.height / 4.0f,
            logoSizeF.width / 2,
            logoSizeF.height / 2);

        for (auto& button : sceneButtons)
        {
            e.FillRect(palette.wheat, button.bounds.x - button.bounds.width / 2, button.bounds.y - button.bounds.height / 2, button.bounds.width, button.bounds.height);
            e.DrawString(button.text, palette.black, button.bounds.x, button.bounds.y, true);
        }
    }

}  // namespace Forradia
