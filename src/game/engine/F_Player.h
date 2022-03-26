#pragma once
#include "framework/F_Inventory.h"
#include "../core/F_Point2F.h"

namespace Forradia
{

class F_Engine;

class F_Player
{

public:

    F_Player(F_Engine& engine) : Engine(engine) {}

    // Argument grouping for UpdateKboardMovement()
    class MovementInstruction
    {

    public:
        bool TryMoveForward = false;
        bool TryMoveRight = false;
        bool TryMoveBack = false;
        bool TryMoveLeft = false;

    };

    // Game loop related
    void ResetForNewFrame();

    // Player actions
    void Jump();

    // Update operations
    void UpdateDestMovement();
    void UpdateKboardMovement(MovementInstruction instr);
    void UpdateRotation(float newFacingAngle);
    void UpdateJumping();

    // Localization
    int CurrentMapArea = 0;
    F_Point2F Position = { 50.0f, 50.0f };
    float PositionZ = 0.0f;

    // Movement
    int TickLastMove = 0;
    int MoveSpeed = 30;
    float StepSize = 3.0f;
    F_Point2F MoveDestination = { -1, -1 };
    float StepMultiplier = 0.1f;

    // Player rotation
    float FacingAngle = 0.0f;
    float FacingAngleRotated = 0.0f;

    // Rendering
    float PlayerSize = 0.6f;
    bool IsWalking = false;

    // Jumping
    bool IsJumping = false;
    int JumpDuration = 600;
    int TickStartJumping = 0;
    float MaxJumpHeight = 1.0f;

    // Composition
    F_Inventory Inventory;

    // Object usage
    SPtr<F_Object> ObjectBeingUsed = nullptr;


private:

    F_Engine& Engine;

};

}
