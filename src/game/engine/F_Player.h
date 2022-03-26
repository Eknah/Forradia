
#pragma once
#include "framework/F_Inventory.h"
#include "../core/F_Point2F.h"
#include "framework/F_Actor.h"
#include "framework/actor_modules/F_ActorModuleJumping.h"
#include "../core/Aliases.h"

namespace Forradia
{

class F_Engine;

class F_Player : public F_Actor
{

public:

    F_Player(F_Engine& engine) : Engine(engine)
    {
        AddModule("ModuleJumping", ModuleJumping);
    }

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

    // Update operations
    void UpdateDestMovement();
    void UpdateKboardMovement(MovementInstruction instr);
    void UpdateRotation(float newFacingAngle);

    void UpdatePlayer()
    {
        Update();
    }

    // Localization
    int CurrentMapArea = 0;
    F_Point2F Position = { 50.0f, 50.0f };

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

    // Composition
    F_Inventory Inventory;

    // Object usage
    SPtr<F_Object> ObjectBeingUsed = nullptr;

    F_ActorModuleJumping ModuleJumping = F_ActorModuleJumping();


private:

    F_Engine& Engine;

};

}
