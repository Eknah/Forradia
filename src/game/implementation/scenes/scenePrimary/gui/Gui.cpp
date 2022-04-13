// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "Gui.h"
#include "../engine/Engine.h"
#include "GuiWindowInventory.h"

namespace Forradia
{

    void Gui::Initialize()
    {
        windows.clear();
        windows.insert(
            { "Inventory", std::make_unique<GuiWindowInventory>(
                              e, "Inventory", RectF{0.1f, 0.1f, 0.2f, 0.7f}) });
    }

    void Gui::Update()
    {
        auto mousePositionF = utils.GetMousePosF();

        if (boundsButtonInventory.ContainsPoint(mousePositionF))
            e.customCursor.cursorType = CursorTypes::Hovering;

        if (boundsButtonCharacter.ContainsPoint(mousePositionF))
            e.customCursor.cursorType = CursorTypes::Hovering;

        if (boundsButtonSystem.ContainsPoint(mousePositionF))
            e.customCursor.cursorType = CursorTypes::Hovering;

        for (auto& [key, window] : windows)
            window->Update();
    }

    void Gui::Render()
    {

        guiMinimap.Render();

        auto MousePositionF = utils.GetMousePosF();

        if (boundsButtonInventory.ContainsPoint(MousePositionF))
            e.FillRectangle({ 100, 200, 255, 100 }, boundsButtonInventory.x,
                boundsButtonInventory.y, boundsButtonInventory.width,
                boundsButtonInventory.height);
        else
            e.FillRectangle({ 0, 150, 255, 100 }, boundsButtonInventory.x,
                boundsButtonInventory.y, boundsButtonInventory.width,
                boundsButtonInventory.height);

        e.DrawRectangle({ 255, 255, 255, 100 }, boundsButtonInventory.x,
            boundsButtonInventory.y, boundsButtonInventory.width,
            boundsButtonInventory.height);
        e.DrawString("Inventory [F2]", { 255, 255, 255, 255 },
            boundsButtonInventory.x + boundsButtonInventory.width / 2,
            boundsButtonInventory.y + boundsButtonInventory.height / 2,
            true);

        if (boundsButtonCharacter.ContainsPoint(MousePositionF))
            e.FillRectangle({ 100, 200, 255, 100 }, boundsButtonCharacter.x,
                boundsButtonCharacter.y, boundsButtonCharacter.width,
                boundsButtonCharacter.height);
        else
            e.FillRectangle({ 0, 150, 255, 100 }, boundsButtonCharacter.x,
                boundsButtonCharacter.y, boundsButtonCharacter.width,
                boundsButtonCharacter.height);

        e.DrawRectangle({ 255, 255, 255, 100 }, boundsButtonCharacter.x,
            boundsButtonCharacter.y, boundsButtonCharacter.width,
            boundsButtonCharacter.height);
        e.DrawString("Character [F1]", { 255, 255, 255, 255 },
            boundsButtonCharacter.x + boundsButtonCharacter.width / 2,
            boundsButtonCharacter.y + boundsButtonCharacter.height / 2,
            true);

        if (boundsButtonSystem.ContainsPoint(MousePositionF))
            e.FillRectangle({ 100, 200, 255, 100 }, boundsButtonSystem.x,
                boundsButtonSystem.y, boundsButtonSystem.width,
                boundsButtonSystem.height);
        else
            e.FillRectangle({ 0, 150, 255, 100 }, boundsButtonSystem.x,
                boundsButtonSystem.y, boundsButtonSystem.width,
                boundsButtonSystem.height);

        e.DrawRectangle({ 255, 255, 255, 100 }, boundsButtonSystem.x,
            boundsButtonSystem.y, boundsButtonSystem.width,
            boundsButtonSystem.height);
        e.DrawString("System [F3]", { 255, 255, 255, 255 },
            boundsButtonSystem.x + boundsButtonSystem.width / 2,
            boundsButtonSystem.y + boundsButtonSystem.height / 2, true);
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

        if (boundsButtonInventory.ContainsPoint(mousePositionF))
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

}  // namespace Forradia
