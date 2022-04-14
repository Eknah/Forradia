// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "Gui.h"
#include "../engine/Engine.h"
#include "InventoryWindow.h"

namespace Forradia
{

    void Gui::Init()
    {
        windows.clear();
        windows.insert
        ({
            "Inventory", std::make_unique<InventoryWindow>( e, "Inventory", RectF{0.1f, 0.1f, 0.2f, 0.7f})
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
    }

    void Gui::Render()
    {

        minimap.Render();

        auto mousePosF = utils.GetMousePosF();

        if (boundsInvBtn.Contains(mousePosF))
            e.FillRect(palette.lightMediumBlueSemiTrans, boundsInvBtn);
        else
            e.FillRect(palette.mediumBlueSemiTrans, boundsInvBtn);

        e.DrawRect(palette.white, boundsInvBtn);

        e.DrawString("Inventory [F2]", palette.white, boundsInvBtn.GetCenter(), true);

        if (boundsCharBtn.Contains(mousePosF))
            e.FillRect(palette.lightMediumBlueSemiTrans, boundsCharBtn);
        else
            e.FillRect(palette.mediumBlueSemiTrans, boundsCharBtn);

        e.DrawRect(palette.white, boundsCharBtn);

        e.DrawString("Character [F1]", palette.white, boundsCharBtn.GetCenter(), true);

        if (boundsSysBtn.Contains(mousePosF))
            e.FillRect(palette.lightMediumBlueSemiTrans, boundsSysBtn);
        else
            e.FillRect(palette.mediumBlueSemiTrans, boundsSysBtn);

        e.DrawRect(palette.white, boundsSysBtn);

        e.DrawString("System [F3]", palette.white, boundsSysBtn.GetCenter(), true);

        console.Render();

        for (auto& [Key, Window] : windows)
            Window->Render();

    }

    bool Gui::DoMouseDown(Uint8 mouseButton)
    {
        for (auto& [key, window] : windows)
        {
            auto clickedInWindow = window->DoMouseDown(mouseButton);

            if (clickedInWindow)
                return true;
        }

        auto mousePositionF = utils.GetMousePosF();

        if (boundsInvBtn.Contains(mousePositionF))
        {
            windows.at("Inventory")->visible = !windows.at("Inventory")->visible;

            return true;
        }

        return false;
    }

    void Gui::DoMouseUp()
    {
        for (auto& [key, window] : windows)
            window->DoMouseUp();
    }

    void Gui::DoKeyDown(SDL_Keycode key)
    {
        console.DoKeyDown(key);
    }

}  // namespace Forradia
