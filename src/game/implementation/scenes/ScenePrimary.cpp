// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ScenePrimary.h"
#include "../engine/Engine.h"
#include "implementation/functionality/actor/modules/CoreMovementModule.h"

namespace Forradia
{

    void ScenePrimary::Enter()
    {
        gui.Initialize();
        gui.console.Print("You have entered Forradia");
    }

    void ScenePrimary::Update()
    {
        auto& keys = e.keyboardHandler.keysBeingPressed;
        auto& player = e.GetPlayer();

        player.ResetForNewFrame();

        if (!SDL_IsTextInputActive())
        {
            char moveInstruction = DirNone;

            if (keys->count(SDLK_w))
                moveInstruction |= DirForward;

            if (keys->count(SDLK_d))
                moveInstruction |= DirRight;

            if (keys->count(SDLK_s))
                moveInstruction |= DirBack;

            if (keys->count(SDLK_a))
                moveInstruction |= DirLeft;

            player.GetModule<DirectionMovementModule>().moveInstruction =
                moveInstruction;

            if (moveInstruction & DirForward || moveInstruction & DirRight ||
                moveInstruction & DirBack || moveInstruction & DirLeft)
            {
                *player.GetModule<CoreMovementModule>().facingAngle = camera.lookingAngle;
                player.GetModule<CoreMovementModule>().dest = { -1, -1 };
            }

            auto turnRight = keys->count(SDLK_e);
            auto turnLeft = keys->count(SDLK_q);

            if (turnRight)
            {
                camera.Update(GetId("Right"), *e.mouseHandler.wheelAmount);
            }
            else if (turnLeft)
            {
                camera.Update(GetId("Left"), *e.mouseHandler.wheelAmount);
            }
            else
            {
                camera.Update(0, *e.mouseHandler.wheelAmount);
            }

            if (e.keyboardHandler.keysBeenFired->count(SDLK_F2))
                gui.windows.at("Inventory")->visible =
                !gui.windows.at("Inventory")->visible;

            if (e.keyboardHandler.keysBeenFired->count(SDLK_SPACE) > 0)
                e.GetPlayer().GetModule<JumpingModule>().Jump();
        }
        camera.UpdateCameraMovement();

        if (e.mouseHandler.rightButtonDown)
            *player.GetModule<CoreMovementModule>().facingAngle = camera.lookingAngle;


        if (e.mouseHandler.rightButtonDown)
            e.customCursor.cursorType = CursorTypes::Hidden;

        for (auto& [key, mobActor] : e.GetCurrMapArea().mobActorsMirror)
        {
            mobActor.get()->Update();
        }

        player.Update();
        gui.Update();

        if (e.keyboardHandler.keysBeenFired->count(SDLK_RETURN))
        {
            gui.console.ToggleInput();
        }
    }

    void ScenePrimary::Render()
    {
        gameWorldRenderer.Render();
        gui.Render();
    }

    void ScenePrimary::DoMouseDown(Uint8 mouseButton)
    {
        if (e.GetPlayer().GetModule<ObjectUsageModule>().objectBeingUsed !=
            nullptr)
        {
            auto hovered = camera.GetHoveredTile();

            if (e.GetCurrMapArea().tiles[hovered.x][hovered.y].objects.size() >
                0)
                e.GetPlayer().GetModule<ObjectUsageModule>().objectBeingUsed->UseOn(
                    e.GetCurrMapArea().tiles[hovered.x][hovered.y].objects.at(
                        e.GetCurrMapArea()
                        .tiles[hovered.x][hovered.y]
                        .objects.size() -
                        1));

            e.GetPlayer().GetModule<ObjectUsageModule>().objectBeingUsed
                = nullptr;

            return;
        }

        auto clickedInGui = gui.DoMouseDown(mouseButton);

        if (clickedInGui)
            return;

        switch (mouseButton)
        {
        case SDL_BUTTON_LEFT:
        {
            e.GetPlayer().GetModule<CoreMovementModule>().dest = {
                camera.GetHoveredTile().x + 0.5f, camera.GetHoveredTile().y + 0.5f };
            break;
        }
        case SDL_BUTTON_RIGHT:
        {
            break;
        }
        }
    }

    void ScenePrimary::DoMouseUp(Uint8 MouseButton)
    {
        gui.DoMouseUp();
    }

}  // namespace Forradia
