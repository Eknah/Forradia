// Copyright (C) 2022  Andreas Åkerberg

#pragma once
#include "../engine/iModule.h"
#include "../engine/cPoint2F.h"

namespace Forradia
{

class cModuleMovement : public iModule
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

    using           iModule::iModule;

    void            ResetForNewFrame() override;
    void            Update() override;

    void            UpdateRotation(float newFacingAngle);

    MovementInstruction
    Instruction;

    bool            IsWalking = false;
    float           FacingAngle = 0.0f;
    float           FacingAngleRotated = 0.0f;
    cPoint2F        MoveDestination = { -1, -1 };

private:

    void            UpdateDirectionalMovement();
    void            UpdateDestinationMovement();

    unsigned int    TickLastMove = 0;
    int             MoveSpeed = 30;
    float           StepSize = 3.0f;
    float           StepMultiplier = 0.1f;

};

}
