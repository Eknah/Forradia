// Copyright (C) 2022  Andreas Åkerberg

#include "CommonExternal.h"
#include "cScenePrimary.h"
#include "../engine/cEngine.h"

namespace Forradia
{

void cScenePrimary::Enter()
{
    Gui.Initialize();
}

void cScenePrimary::Update()
{
    auto& Keys = Engine.KeyboardHandler.KeysBeingPressed;
    auto& Player = Engine.Player;

    Player.ResetForNewFrame();

    auto Instruction = cModuleMovement::MovementInstruction();

    Instruction.TryMoveForward = Keys.count(SDLK_w);
    Instruction.TryMoveRight = Keys.count(SDLK_d);
    Instruction.TryMoveBack = Keys.count(SDLK_s);
    Instruction.TryMoveLeft = Keys.count(SDLK_a);

    Player.GetModule<cModuleMovement>().Instruction = Instruction;

    if (Instruction.TryMoveForward || Instruction.TryMoveRight || Instruction.TryMoveBack || Instruction.TryMoveLeft)
    {
        Player.GetModule<cModuleMovement>().FacingAngle = Camera.LookingAngle;
        Player.GetModule<cModuleMovement>().MoveDestination = { -1, -1 };
    }

    auto TurnRight = Keys.count(SDLK_e);
    auto TurnLeft = Keys.count(SDLK_q);

    if (TurnRight)
    {
        Camera.Update(GetId("Right"), Engine.MouseHandler.WheelAmount);
        Player.GetModule<cModuleMovement>().UpdateRotation(Camera.LookingAngle);
    }
    else if (TurnLeft)
    {
        Camera.Update(GetId("Left"), Engine.MouseHandler.WheelAmount);
        Player.GetModule<cModuleMovement>().UpdateRotation(Camera.LookingAngle);
    }
    else
    {
        Camera.Update(0, Engine.MouseHandler.WheelAmount);
    }

    if (Engine.KeyboardHandler.KeysBeenFired.count(SDLK_F2))
        Gui.Windows.at("Inventory")->Visible = !Gui.Windows.at("Inventory")->Visible;

    Camera.UpdateCameraMovement();

    if (Engine.MouseHandler.RightButtonDown)
        Player.GetModule<cModuleMovement>().FacingAngle = Camera.LookingAngle;

    if (Engine.KeyboardHandler.KeysBeenFired.count(SDLK_SPACE) > 0)
        Engine.Player.GetModule<cModuleJumping>().Jump();

    if (Engine.MouseHandler.RightButtonDown)
        Engine.CustomCursor.CursorType = eCursorTypes::Hidden;

    Player.Update();
    MobsEngine.Update();
    Gui.Update();
}

void cScenePrimary::Render()
{
    GameWorldRenderer.Render();
    Gui.Render();
}

void cScenePrimary::DoMouseDown(Uint8 MouseButton)
{
    if (Engine.Player.GetModule<cModuleObjectUsage>().ObjectBeingUsed != nullptr)
    {
        auto Hovered = Camera.GetHoveredTile();

        if (Engine.GetCurrentMapArea().Tiles[Hovered.X][Hovered.Y].Objects.size() > 0)
            Engine.Player.GetModule<cModuleObjectUsage>().ObjectBeingUsed->UseOn(Engine.GetCurrentMapArea().Tiles[Hovered.X][Hovered.Y].Objects.at(Engine.GetCurrentMapArea().Tiles[Hovered.X][Hovered.Y].Objects.size() - 1));

        Engine.Player.GetModule<cModuleObjectUsage>().ObjectBeingUsed = nullptr;

        return;
    }

    auto ClickedInGui = Gui.DoMouseDown(MouseButton);

    if (ClickedInGui)
        return;

    switch (MouseButton)
    {
    case SDL_BUTTON_LEFT:
    {
        Engine.Player.GetModule<cModuleMovement>().MoveDestination = { Camera.GetHoveredTile().X + 0.5f, Camera.GetHoveredTile().Y + 0.5f };
        break;
    }
    case SDL_BUTTON_RIGHT:
    {
        break;
    }
    }
}

void cScenePrimary::DoMouseUp(Uint8 MouseButton)
{
    Gui.DoMouseUp();
}

}
