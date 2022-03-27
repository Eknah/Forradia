
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
    auto& keys = Engine.KeyboardHandler.KeysBeingPressed;
    auto& player = Engine.Player;

    player.ResetForNewFrame();

    auto instruction = cModuleMovement::MovementInstruction();

    instruction.TryMoveForward = keys.count(SDLK_w);
    instruction.TryMoveRight = keys.count(SDLK_d);
    instruction.TryMoveBack = keys.count(SDLK_s);
    instruction.TryMoveLeft = keys.count(SDLK_a);

    player.GetModule<cModuleMovement>().Instruction = instruction;

    if (instruction.TryMoveForward || instruction.TryMoveRight || instruction.TryMoveBack || instruction.TryMoveLeft)
    {
        player.GetModule<cModuleMovement>().FacingAngle = Camera.LookingAngle;
        player.GetModule<cModuleMovement>().MoveDestination = { -1, -1 };
    }

    auto turn_right = keys.count(SDLK_e);
    auto turn_left = keys.count(SDLK_q);

    if (turn_right)
    {
        Camera.Update(GetId("Right"), Engine.MouseHandler.WheelAmount);
        player.GetModule<cModuleMovement>().UpdateRotation(Camera.LookingAngle);
    }
    else if (turn_left)
    {
        Camera.Update(GetId("Left"), Engine.MouseHandler.WheelAmount);
        player.GetModule<cModuleMovement>().UpdateRotation(Camera.LookingAngle);
    }
    else
    {
        Camera.Update(0, Engine.MouseHandler.WheelAmount);
    }

    if (Engine.KeyboardHandler.KeysBeenFired.count(SDLK_F2))
    {
        Gui.Windows.at("Inventory")->Visible = !Gui.Windows.at("Inventory")->Visible;
    }

    Camera.UpdateCameraMovement();

    if (Engine.MouseHandler.RightButtonDown)
    {
        player.GetModule<cModuleMovement>().FacingAngle = Camera.LookingAngle;
    }

    if (Engine.KeyboardHandler.KeysBeenFired.count(SDLK_SPACE) > 0)
        Engine.Player.GetModule<cModuleJumping>().Jump();

    if (Engine.MouseHandler.RightButtonDown)
        Engine.CustomCursor.CursorType = eCursorTypes::Hidden;

    //player.UpdateJumping();
    player.Update();
    MobsEngine.Update();
    Gui.Update();
}

void cScenePrimary::Render()
{
    GameWorldRenderer.Render();
    Gui.Render();
}

void cScenePrimary::DoMouseDown(Uint8 mouseButton)
{
    if (Engine.Player.GetModule<cModuleObjectUsage>().ObjectBeingUsed != nullptr)
    {
        auto hovered = Camera.GetHoveredTile();

        if (Engine.GetCurrentMapArea().Tiles[hovered.X][hovered.Y].Objects.size() > 0)
            Engine.Player.GetModule<cModuleObjectUsage>().ObjectBeingUsed->UseOn(Engine.GetCurrentMapArea().Tiles[hovered.X][hovered.Y].Objects.at(Engine.GetCurrentMapArea().Tiles[hovered.X][hovered.Y].Objects.size() - 1));

        Engine.Player.GetModule<cModuleObjectUsage>().ObjectBeingUsed = nullptr;

        return;
    }

    auto clicked_in_gui = Gui.DoMouseDown(mouseButton);

    if (clicked_in_gui)
        return;

    switch (mouseButton)
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

void cScenePrimary::DoMouseUp(Uint8 mouseButton)
{
    Gui.DoMouseUp();
}

}
