
#pragma once
#include "framework/F_Inventory.h"
#include "framework/F_Actor.h"
#include "framework/actor_modules/F_ActorModuleJumping.h"
#include "framework/actor_modules/F_ActorModuleMovement.h"
#include "../core/Aliases.h"

namespace Forradia
{


class F_Player : public F_Actor
{

public:

    F_Player(F_IEngine& engine) : F_Actor(engine)
    {
        AddModule<F_ActorModuleJumping>("ModuleJumping");
        AddModule<F_ActorModuleMovement>("ModuleMovement");
    }


    void UpdateRotation(float newFacingAngle);

    void SetMovementInstruction(F_ActorModuleMovement::MovementInstruction Instruction_)
    {
        GetModule<F_ActorModuleMovement>("ModuleMovement").Instruction = Instruction_;
    }

    // Rendering
    float PlayerSize = 0.6f;

    // Composition
    F_Inventory Inventory;

    // Object usage
    SPtr<F_Object> ObjectBeingUsed = nullptr;


};

}
