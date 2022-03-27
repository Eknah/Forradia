
#pragma once
#include "framework/F_Inventory.h"
#include "../core/F_Point2F.h"
#include "framework/F_Actor.h"
#include "framework/actor_modules/F_ActorModuleJumping.h"
#include "framework/actor_modules/F_ActorModuleMovement.h"
#include "../core/Aliases.h"

namespace Forradia
{

class F_IEngine;

class F_Player : public F_Actor
{

public:

    F_Player(F_IEngine& engine) : Engine(engine), ModuleJumping(engine, *this), ModuleMovement(engine, *this)
    {
        AddModule("ModuleJumping", ModuleJumping);
        AddModule("ModuleMovement", ModuleMovement);
    }


    void UpdateRotation(float newFacingAngle);

    void SetMovementInstruction(F_ActorModuleMovement::MovementInstruction Instruction_)
    {
        ModuleMovement.Instruction = Instruction_;
    }

    // Rendering
    float PlayerSize = 0.6f;

    // Composition
    F_Inventory Inventory;

    // Object usage
    SPtr<F_Object> ObjectBeingUsed = nullptr;

    F_ActorModuleJumping ModuleJumping;
    F_ActorModuleMovement ModuleMovement;


private:

    F_IEngine& Engine;

};

}
