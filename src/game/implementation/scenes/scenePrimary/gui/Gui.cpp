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
            e.customCursor.cursType = CursorTypes::Hovering;

        if (boundsCharBtn.Contains(mousePosF))
            e.customCursor.cursType = CursorTypes::Hovering;

        if (boundsSysBtn.Contains(mousePosF))
            e.customCursor.cursType = CursorTypes::Hovering;

        for (auto& [key, window] : windows)
            window->Update();

        console.Update();
    }

    void Gui::Render()
    {

        minimap.Render();

        auto mousePosF = utils.GetMousePosF();

        if (boundsInvBtn.Contains(mousePosF))
            e.FillRect(pal.gray, boundsInvBtn);
        else
            e.FillRect(pal.darkGray, boundsInvBtn);

        e.DrawRect(pal.white, boundsInvBtn);

        e.DrawString("Inventory [F2]", pal.white, boundsInvBtn.GetCenter(), true);

        if (boundsCharBtn.Contains(mousePosF))
            e.FillRect(pal.gray, boundsCharBtn);
        else
            e.FillRect(pal.darkGray, boundsCharBtn);

        e.DrawRect(pal.white, boundsCharBtn);

        e.DrawString("Character [F1]", pal.white, boundsCharBtn.GetCenter(), true);

        if (boundsSysBtn.Contains(mousePosF))
            e.FillRect(pal.gray, boundsSysBtn);
        else
            e.FillRect(pal.darkGray, boundsSysBtn);

        e.DrawRect(pal.white, boundsSysBtn);

        e.DrawString("System [F3]", pal.white, boundsSysBtn.GetCenter(), true);

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
