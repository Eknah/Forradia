// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "Gui.h"
#include "../engine/Engine.h"
#include "InventoryWindow.h"

namespace Forradia
{

    void Gui::Initialize()
    {
        windows.clear();
        windows.insert(
            { "Inventory", std::make_unique<InventoryWindow>(
                              e, "Inventory", RectF{0.1f, 0.1f, 0.2f, 0.7f}) });
    }

    void Gui::Update()
    {
        auto mousePositionF = utils.GetMousePosF();

        if (boundsInventoryBtn.ContainsPoint(mousePositionF))
            e.customCursor.cursorType = CursorTypes::Hovering;

        if (boundsCharacterBtn.ContainsPoint(mousePositionF))
            e.customCursor.cursorType = CursorTypes::Hovering;

        if (boundsSystemBtn.ContainsPoint(mousePositionF))
            e.customCursor.cursorType = CursorTypes::Hovering;

        for (auto& [key, window] : windows)
            window->Update();
    }

    void Gui::Render()
    {

        minimap.Render();

        auto MousePositionF = utils.GetMousePosF();

        if (boundsInventoryBtn.ContainsPoint(MousePositionF))
            e.FillRect({ 100, 200, 255, 100 }, boundsInventoryBtn.x,
                boundsInventoryBtn.y, boundsInventoryBtn.w,
                boundsInventoryBtn.h);
        else
            e.FillRect({ 0, 150, 255, 100 }, boundsInventoryBtn.x,
                boundsInventoryBtn.y, boundsInventoryBtn.w,
                boundsInventoryBtn.h);

        e.DrawRect({ 255, 255, 255, 100 }, boundsInventoryBtn.x,
            boundsInventoryBtn.y, boundsInventoryBtn.w,
            boundsInventoryBtn.h);
        e.DrawString("Inventory [F2]", { 255, 255, 255, 255 },
            boundsInventoryBtn.x + boundsInventoryBtn.w / 2,
            boundsInventoryBtn.y + boundsInventoryBtn.h / 2,
            true);

        if (boundsCharacterBtn.ContainsPoint(MousePositionF))
            e.FillRect({ 100, 200, 255, 100 }, boundsCharacterBtn.x,
                boundsCharacterBtn.y, boundsCharacterBtn.w,
                boundsCharacterBtn.h);
        else
            e.FillRect({ 0, 150, 255, 100 }, boundsCharacterBtn.x,
                boundsCharacterBtn.y, boundsCharacterBtn.w,
                boundsCharacterBtn.h);

        e.DrawRect({ 255, 255, 255, 100 }, boundsCharacterBtn.x,
            boundsCharacterBtn.y, boundsCharacterBtn.w,
            boundsCharacterBtn.h);
        e.DrawString("Character [F1]", { 255, 255, 255, 255 },
            boundsCharacterBtn.x + boundsCharacterBtn.w / 2,
            boundsCharacterBtn.y + boundsCharacterBtn.h / 2,
            true);

        if (boundsSystemBtn.ContainsPoint(MousePositionF))
            e.FillRect({ 100, 200, 255, 100 }, boundsSystemBtn.x,
                boundsSystemBtn.y, boundsSystemBtn.w,
                boundsSystemBtn.h);
        else
            e.FillRect({ 0, 150, 255, 100 }, boundsSystemBtn.x,
                boundsSystemBtn.y, boundsSystemBtn.w,
                boundsSystemBtn.h);

        e.DrawRect({ 255, 255, 255, 100 }, boundsSystemBtn.x,
            boundsSystemBtn.y, boundsSystemBtn.w,
            boundsSystemBtn.h);
        e.DrawString("System [F3]", { 255, 255, 255, 255 },
            boundsSystemBtn.x + boundsSystemBtn.w / 2,
            boundsSystemBtn.y + boundsSystemBtn.h / 2, true);
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

        if (boundsInventoryBtn.ContainsPoint(mousePositionF))
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
