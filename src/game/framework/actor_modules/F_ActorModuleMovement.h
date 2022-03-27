
#pragma once
#include "F_IActorModule.h"
#include "../core/F_Point2F.h"

namespace Forradia
{

class F_ActorModuleMovement : public F_IActorModule
{

public:

    class MovementInstruction
    {

    public:
        bool TryMoveForward = false;
        bool TryMoveRight = false;
        bool TryMoveBack = false;
        bool TryMoveLeft = false;

    };

    using F_IActorModule::F_IActorModule;

    void ResetForNewFrame() override;
    void Update() override;

    MovementInstruction Instruction;
    bool IsWalking = false;
    float FacingAngle = 0.0f;
    float FacingAngleRotated = 0.0f;
    F_Point2F MoveDestination = { -1, -1 };

private:

    void UpdateDirectionalMovement();
    void UpdateDestinationMovement();

    int TickLastMove = 0;
    int MoveSpeed = 30;
    float StepSize = 3.0f;
    float StepMultiplier = 0.1f;

};

}
