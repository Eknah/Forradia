#include "Pch.h"
#include "CScenePrimary.h"
#include "../Hidden/CEngine.h"
namespace Forradia
{
	void CScenePrimary::Enter()
	{
		Gui.InitializeEngine();
	}
	void CScenePrimary::Update()
	{
		auto& keys = Engine.KeyboardHandler.KeysBeingPressed;
		auto& player = Engine.Player;
		player.ResetForNewFrame();
		player.UpdateDestMovement();
		auto instruction = CPlayer::MovementInstruction();
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
			Camera.Update(Hash("Right"), Engine.MouseHandler.WheelAmount);
			player.UpdateRotation(Camera.LookingAngle);
		}
		else if (turn_left)
		{
			Camera.Update(Hash("Left"), Engine.MouseHandler.WheelAmount);
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
			Engine.Player.Jump();
		if (Engine.MouseHandler.RightButtonDown)
			Engine.CustomCursor.CursorType = ECursorTypes::Hidden;
		player.UpdateJumping();
		MobsEngine.Update();
		Gui.Update();
	}
	void CScenePrimary::Render()
	{
		GameWorldRenderer.Render();
		Gui.Render();
	}
	void CScenePrimary::DoMouseDown(Uint8 mouseButton)
	{
		if (Engine.Player.ObjectBeingUsed != nullptr)
		{
			auto [hovered_x, hovered_y] = Camera.GetHoveredTile();
			if (Engine.GetCurrentMapArea().Tiles[hovered_x][hovered_y].Objects.size() > 0)
				Engine.Player.ObjectBeingUsed->UseOn(Engine.GetCurrentMapArea().Tiles[hovered_x][hovered_y].Objects.at(Engine.GetCurrentMapArea().Tiles[hovered_x][hovered_y].Objects.size() - 1));
			Engine.Player.ObjectBeingUsed = nullptr;
			return;
		}
		auto clicked_in_gui = Gui.DoMouseDown(mouseButton);
		if (clicked_in_gui) return;
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
	void CScenePrimary::DoMouseUp(Uint8 mouseButton)
	{
		Gui.DoMouseUp();
	}
}
