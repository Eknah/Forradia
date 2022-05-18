// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "Gui.h"
#include "Engine.h"
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
            e.cursor.type = CursorTypes::Hovering;

        if (boundsCharBtn.Contains(mousePosF))
            e.cursor.type = CursorTypes::Hovering;

        if (boundsSysBtn.Contains(mousePosF))
            e.cursor.type = CursorTypes::Hovering;

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
            e.FillRect(LightMediumBlueSemiTrans, boundsInvBtn);
        else
            e.FillRect(MediumBlueSemiTrans, boundsInvBtn);

        e.DrawRect(White, boundsInvBtn);

        e.DrawString("Inventory [F2]", White, boundsInvBtn.GetCenter(), true);

        if (boundsCharBtn.Contains(mousePosF))
            e.FillRect(LightMediumBlueSemiTrans, boundsCharBtn);
        else
            e.FillRect(MediumBlueSemiTrans, boundsCharBtn);

        e.DrawRect(White, boundsCharBtn);

        e.DrawString("Character [F1]", White, boundsCharBtn.GetCenter(), true);

        if (boundsSysBtn.Contains(mousePosF))
            e.FillRect(LightMediumBlueSemiTrans, boundsSysBtn);
        else
            e.FillRect(MediumBlueSemiTrans, boundsSysBtn);

        e.DrawRect(White, boundsSysBtn);

        e.DrawString("System [F3]", White, boundsSysBtn.GetCenter(), true);

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

    void Gui::MouseUp(Uint8 mouseButton)
    {
        for (auto& [key, window] : windows)
            window->MouseUp();

        rightClickMenu.MouseUp(mouseButton);
    }

    void Gui::KeyDown(SDL_Keycode key)
    {
        console.KeyDown(key);
    }
}