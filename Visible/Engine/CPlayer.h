#pragma once
namespace Forradia
{

	class CEngine;

	class CPlayer
	{

	public:
		CPlayer(CEngine& engine) : Engine(engine) {}

		class MovementInstruction
		{

		public:
			bool TryMoveForward = False;
			bool TryMoveRight = False;
			bool TryMoveBack = False;
			bool TryMoveLeft = False;

		};

		void ResetForNewFrame();
		void Jump();
		void UpdateDestMovement();
		void UpdateKboardMovement(MovementInstruction instr);
		void UpdateRotation(float newFacingAngle);
		void UpdateJumping();

		float PlayerSize = 0.6f;
		bool IsJumping = False;
		int JumpDuration = 600;
		int TickStartJumping = 0;
		float MaxJumpHeight = 1.0f;
		CPoint2F Position = { 50.0f, 50.0f };
		float PositionZ = 0.0f;
		int TickLastMove = 0;
		int MoveSpeed = 30;
		float StepSize = 3.0f;
		float FacingAngle = 0.0f;
		float FacingAngleRotated = 0.0f;
		bool IsWalking = False;
		CPoint2F MoveDestination = { -1, -1 };
		float StepMultiplier = 0.1f;
		CInventory Inventory;
                SPtr<CObject> ObjectBeingUsed = nullptr;
		int CurrentMapArea = 0;

	private:

		CEngine& Engine;

	};

}
