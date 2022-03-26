
#include "CommonExternal.h"
#include "F_ScenePrimary.h"
#include "../core/F_Engine.h"

namespace Forradia
{

void F_ScenePrimary::Enter()
{
    Gui.Initialize();
}

void F_ScenePrimary::Update()
{
    auto& keys = Engine.KeyboardHandler.KeysBeingPressed;
    auto& player = Engine.Player;

    player.ResetForNewFrame();
    player.UpdateDestMovement();

    auto instruction = F_Player::MovementInstruction();

    instruction.TryMoveForward = keys.count(SDLK_w);
    instruction.TryMoveRight = keys.count(SDLK_d);
    instruction.TryMoveBack = keys.count(SDLK_s);
    instruction.TryMoveLeft = keys.count(SDLK_a);

    player.UpdateKboardMovement(instruction);

    if (instruction.TryMoveForward || instruction.TryMoveRight || instruction.TryMoveBack || instruction.TryMoveLeft)
    {
        player.FacingAngle = Camera.LookingAngle;
        player.MoveDestination = { -1, -1 };
    }

    auto turn_right = keys.count(SDLK_e);
    auto turn_left = keys.count(SDLK_q);

    if (turn_right)
    {
        Camera.Update(GetId("Right"), Engine.MouseHandler.WheelAmount);
        player.UpdateRotation(Camera.LookingAngle);
    }
    else if (turn_left)
    {
        Camera.Update(GetId("Left"), Engine.MouseHandler.WheelAmount);
        player.UpdateRotation(Camera.LookingAngle);
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
        player.FacingAngle = Camera.LookingAngle;
    }

    if (Engine.KeyboardHandler.KeysBeenFired.count(SDLK_SPACE) > 0)
        Engine.Player.ModuleJumping.Jump();

    if (Engine.MouseHandler.RightButtonDown)
        Engine.CustomCursor.CursorType = F_ECursorTypes::Hidden;

    //player.UpdateJumping();
    player.UpdatePlayer();
    MobsEngine.Update();
    Gui.Update();
}

void F_ScenePrimary::Render()
{
    GameWorldRenderer.Render();
    Gui.Render();
}

void F_ScenePrimary::DoMouseDown(Uint8 mouseButton)
{
    if (Engine.Player.ObjectBeingUsed != nullptr)
    {
        auto hovered = Camera.GetHoveredTile();

        if (Engine.GetCurrentMapArea().Tiles[hovered.X][hovered.Y].Objects.size() > 0)
            Engine.Player.ObjectBeingUsed->UseOn(Engine.GetCurrentMapArea().Tiles[hovered.X][hovered.Y].Objects.at(Engine.GetCurrentMapArea().Tiles[hovered.X][hovered.Y].Objects.size() - 1));

        Engine.Player.ObjectBeingUsed = nullptr;

        return;
    }

    auto clicked_in_gui = Gui.DoMouseDown(mouseButton);

    if (clicked_in_gui)
        return;

    switch (mouseButton)
    {
    case SDL_BUTTON_LEFT:
    {
        Engine.Player.MoveDestination = { Camera.GetHoveredTile().X + 0.5f, Camera.GetHoveredTile().Y + 0.5f };
        break;
    }
    case SDL_BUTTON_RIGHT:
    {
        break;
    }
    }
}

void F_ScenePrimary::DoMouseUp(Uint8 mouseButton)
{
    Gui.DoMouseUp();
}

}
