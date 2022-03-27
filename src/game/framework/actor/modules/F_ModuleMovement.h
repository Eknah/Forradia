
#pragma once
#include "F_IModule.h"
#include "../engine/F_Point2F.h"

namespace Forradia
{

class F_ModuleMovement : public F_IModule
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

    using F_IModule::F_IModule;

    void ResetForNewFrame() override;
    void Update() override;

    void UpdateRotation(float newFacingAngle);

    MovementInstruction Instruction;
    bool IsWalking = false;
    float FacingAngle = 0.0f;
    float FacingAngleRotated = 0.0f;
    F_Point2F MoveDestination = { -1, -1 };

private:

    void UpdateDirectionalMovement();
    void UpdateDestinationMovement();

    unsigned int TickLastMove = 0;
    int MoveSpeed = 30;
    float StepSize = 3.0f;
    float StepMultiplier = 0.1f;

};

}
