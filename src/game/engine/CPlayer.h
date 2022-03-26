#pragma once
#include "framework/CInventory.h"
#include "../core/CPoint2F.h"

namespace Forradia
{

class CEngine;

class CPlayer
{

public:

    CPlayer(CEngine& engine) : Engine(engine) {}

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
    CPoint2F Position = { 50.0f, 50.0f };
    float PositionZ = 0.0f;

    // Movement
    int TickLastMove = 0;
    int MoveSpeed = 30;
    float StepSize = 3.0f;
    CPoint2F MoveDestination = { -1, -1 };
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
    CInventory Inventory;

    // Object usage
    SPtr<CObject> ObjectBeingUsed = nullptr;


private:

    CEngine& Engine;

};

}
