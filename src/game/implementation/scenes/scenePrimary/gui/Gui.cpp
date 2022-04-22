// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "Gui.h"
#include "../engine/Engine.h"
#include "InventoryWin.h"

namespace Forradia
{

    void Gui::Init()
    {
        windows.clear();
        windows.insert
        ({
            "Inventory", std::make_unique<InventoryWin>( e, "Inventory", RectF{0.1f, 0.1f, 0.2f, 0.7f})
        });
    }

    void Gui::Update()
    {
        auto mousePosF = utils.GetMousePosF();

        if (boundsInvBtn.Contains(mousePosF))
            _ cursor.type = CursorTypes::Hovering;

        if (boundsCharBtn.Contains(mousePosF))
            _ cursor.type = CursorTypes::Hovering;

        if (boundsSysBtn.Contains(mousePosF))
            _ cursor.type = CursorTypes::Hovering;

        for (auto& [key, window] : windows)
            window->Update();

        console.Update();
    }

    void Gui::Render()
    {
        using namespace Palette;

        minimap.Render();
        rightClickMenu.Render();

        auto mousePosF = utils.GetMousePosF();

        if (boundsInvBtn.Contains(mousePosF))
            _ FillRect(Gray, boundsInvBtn);
        else
            _ FillRect(DarkGray, boundsInvBtn);

        _ DrawRect(White, boundsInvBtn);

        _ DrawString("Inventory [F2]", White, boundsInvBtn.GetCenter(), true);

        if (boundsCharBtn.Contains(mousePosF))
            _ FillRect(Gray, boundsCharBtn);
        else
            _ FillRect(DarkGray, boundsCharBtn);

        _ DrawRect(White, boundsCharBtn);

        _ DrawString("Character [F1]", White, boundsCharBtn.GetCenter(), true);

        if (boundsSysBtn.Contains(mousePosF))
            _ FillRect(Gray, boundsSysBtn);
        else
            _ FillRect(DarkGray, boundsSysBtn);

        _ DrawRect(White, boundsSysBtn);

        _ DrawString("System [F3]", White, boundsSysBtn.GetCenter(), true);

        console.Render();

        for (auto& [Key, Window] : windows)
            Window->Render();

    }

    bool Gui::MouseDown(Uint8 mouseButton)
    {
        for (auto& [key, window] : windows)
        {
            auto clickedInWindow = window->MouseDown(mouseButton);

            if (clickedInWindow)
                return true;
        }

        auto mousePositionF = utils.GetMousePosF();

        if (boundsInvBtn.Contains(mousePositionF))
        {
            windows.at("Inventory")->visible = !windows.at("Inventory")->visible;

            return true;
        }

        if (console.MouseDown(mouseButton))
        {
            return true;
        }

        rightClickMenu.MouseDown(mouseButton);

        return false;
    }

    void Gui::MouseUp()
    {
        for (auto& [key, window] : windows)
            window->MouseUp();
    }

    void Gui::KeyDown(SDL_Keycode key)
    {
        console.KeyDown(key);
    }

}  // namespace Forradia
