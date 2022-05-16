// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ScenePrimary.h"
#include "Engine.h"
#include "CoreMovmModule.h"
#include "CraftSkillsModule.h"

namespace Forradia
{

    void ScenePrimary::Enter()
    {
        gui.Init();
        gui.console.Print("You have entered Forradia");
    }

    void ScenePrimary::Update()
    {
        auto& keys = _ keyboardHandler.keysBeingPressed;
        auto& player = _ GetPlayer();

        player.ResetForNewFrame();

        if (!SDL_IsTextInputActive() && _ keyboardHandler.keysBeingPressed->count(SDLK_LCTRL) == 0)
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

            player.GetModule<DirectionMovmModule>().moveInstruction = moveInstruction;

            if (moveInstruction & DirForward || moveInstruction & DirRight ||
                moveInstruction & DirBack || moveInstruction & DirLeft)
            {
                *player.GetModule<CoreMovmModule>().facingAngle = cam.lookingAngle;
                player.GetModule<CoreMovmModule>().dest = { -1, -1 };
            }

            auto turnRight = keys->count(SDLK_e);
            auto turnLeft = keys->count(SDLK_q);

            if (turnRight)
                cam.UpdateRotation(GetId("Right"));
            else if (turnLeft)
                cam.UpdateRotation(GetId("Left"));
            else
                cam.UpdateRotation(0);

            if (_ keyboardHandler.keysBeenFired->count(SDLK_F2))
                gui.windows.at("Inventory")->visible = !gui.windows.at("Inventory")->visible;

            if (_ keyboardHandler.keysBeenFired->count(SDLK_SPACE) > 0)
                _ GetPlayer().GetModule<JumpingModule>().Jump();
        }

        cam.UpdateZoomChange(*_ mouseHandler.wheelAmount);
        cam.UpdateCameraMovm();
        cam.UpdateRayCasting();

        if (_ mouseHandler.rightButtonDown)
            *player.GetModule<CoreMovmModule>().facingAngle = cam.lookingAngle;

        if (_ mouseHandler.rightButtonDown)
            _ cursor.type = CursorTypes::Hidden;

        for (auto i = 0; i < _ GetCurrMapArea().mobActorsMirror.size(); i++)
        {
            _ GetCurrMapArea().mobActorsMirror.at(i).get()->Update();
        }

        player.Update();
        gui.Update();

        if (_ keyboardHandler.keysBeenFired->count(SDLK_RETURN))
            gui.console.ToggleInput();
    }

    void ScenePrimary::Render()
    {
        worldRenderer.Render();
        gui.Render();
    }

    void ScenePrimary::MouseDown(Uint8 mouseButton)
    {
        auto hovered = cam.GetHoveredTile();
        //auto& objectUsage = _ GetPlayer().GetModule<CraftSkillsModule>();
        auto& hoveredTile = _ GetCurrMapArea().tiles[hovered.x][hovered.y];

//        if (objectUsage.objectBeingUsed != nullptr)
//        {

//            if (hoveredTile.objects.size() > 0)
//                objectUsage.objectBeingUsed->UseOn(hoveredTile.objects.at(hoveredTile.objects.size() -1));

//            objectUsage.objectBeingUsed = nullptr;

//            return;
//        }

        auto clickedInGui = gui.MouseDown(mouseButton);

        if (clickedInGui) return;

        switch (mouseButton)
        {
        case SDL_BUTTON_LEFT:
        {
            _ GetPlayer().GetModule<CoreMovmModule>().dest =
            {
                cam.GetHoveredTile().x + 0.5f,
                cam.GetHoveredTile().y + 0.5f
            };
            break;
        }
        case SDL_BUTTON_RIGHT:
        {

            break;
        }
        }
    }

    void ScenePrimary::MouseUp(Uint8 mouseButton)
    {
        gui.MouseUp(mouseButton);
    }

    void ScenePrimary::KeyDown(SDL_Keycode key)
    {
        gui.KeyDown(key);
    }

}  // namespace Forradia
