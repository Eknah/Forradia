// Copyright (C) 2022  Andreas Åkerberg

#include "cModuleMovement.h"
#include "../engine/Aliases.h"
#include "../engine/iEngine.h"
#include "implementation/functionality/actor/cActor.h"

namespace Forradia
{

void cModuleMovement::ResetForNewFrame()
{
    IsWalking = false;
    FacingAngleRotated = FacingAngle;
}

void cModuleMovement::Update()
{
    UpdateDirectionalMovement();
    UpdateDestinationMovement();
}

void cModuleMovement::UpdateRotation(float newFacingAngle)
{
    FacingAngle = newFacingAngle;
}

void cModuleMovement::UpdateDirectionalMovement()
{
    if (!(Ticks() > TickLastMove + MoveSpeed && (Instruction.TryMoveForward || Instruction.TryMoveRight || Instruction.TryMoveBack || Instruction.TryMoveLeft))) return;

    IsWalking = true;

    auto NewX = ParentActor.Position.X;
    auto NewY = ParentActor.Position.Y;
    auto Angle = 0.0f;

    if (Instruction.TryMoveForward)
    {
        Angle = FacingAngle / 180.0f * (float)M_PI - (float)M_PI / 2.0f + 0.0f * (float)M_PI / 2.0f;
    }

    if (Instruction.TryMoveLeft)
    {
        Angle = FacingAngle / 180.0f * (float)M_PI - (float)M_PI / 2.0f + 1.0f * (float)M_PI / 2.0f;
        FacingAngleRotated = FacingAngle + 1 * 90.0f;
    }

    if (Instruction.TryMoveBack)
    {
        Angle =
                FacingAngle / 180.0f * (float)M_PI - (float)M_PI / 2.0f + 2.0f * (float)M_PI / 2.0f;
    }

    if (Instruction.TryMoveRight)
    {
        Angle = FacingAngle / 180.0f * (float)M_PI - (float)M_PI / 2.0f + 3.0f * (float)M_PI / 2.0f;
        FacingAngleRotated = FacingAngle + 3.0f * 90.0f;
    }

    auto DX = -std::cos(Angle) * StepMultiplier;
    auto DY = std::sin(Angle) * StepMultiplier;

    NewX += DX * StepSize;
    NewY += DY * StepSize;

    if (NewX < 0)
        NewX += Engine.GetCurrentMapArea().Size;

    if (NewY < 0)
        NewY += Engine.GetCurrentMapArea().Size;

    if (NewX >= Engine.GetCurrentMapArea().Size)
        NewX -= Engine.GetCurrentMapArea().Size;

    if (NewY >= Engine.GetCurrentMapArea().Size)
        NewY -= Engine.GetCurrentMapArea().Size;

    auto NewXRounded = int(std::round(NewX));
    auto NewYRounded = int(std::round(NewY));

    if (!Engine.GetCurrentMapArea().Tiles[NewXRounded][NewYRounded].MovementBlocked())
    {
        ParentActor.Position.X = NewX;
        ParentActor.Position.Y = NewY;
    }

    if (Engine.GetCurrentMapArea().Tiles[int(NewX)][int(NewY)].WarpToFloor != -1)
    {
        ParentActor.WorldMapCoord.Z = Engine.GetCurrentMapArea().Tiles[int(NewX)][int(NewY)].WarpToFloor;

        auto Angle = FacingAngle / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
        auto DX = -(float)std::cos(Angle) * StepMultiplier;
        auto DY = (float)std::sin(Angle) * StepMultiplier;

        NewX += DX * StepSize * 10;
        NewY += DY * StepSize * 10;

        ParentActor.Position.X = NewX;
        ParentActor.Position.Y = NewY;
    }

    TickLastMove = Ticks();
}

void cModuleMovement::UpdateDestinationMovement()
{
    if (!(Ticks() > TickLastMove + MoveSpeed && MoveDestination.X != -1 && MoveDestination.Y != -1)) return;

    auto DX = MoveDestination.X - ParentActor.Position.X;
    auto DY = MoveDestination.Y - ParentActor.Position.Y;
    auto AbsDX = std::abs(DX);
    auto AbsDY = std::abs(DY);

    if (AbsDX < StepMultiplier && AbsDY < StepMultiplier)
    {
        MoveDestination = { -1, -1 };
    }
    else
    {
        IsWalking = true;
        FacingAngle = (float)std::atan2(-DX, -DY) / (float)M_PI * 180.0f;

        auto Angle = FacingAngle / 180.0f * (float)M_PI - (float)M_PI / 2 + 0 * (float)M_PI / 2;
        auto DX = -(float)std::cos(Angle) * StepMultiplier;
        auto DY = (float)std::sin(Angle) * StepMultiplier;
        auto NewX = ParentActor.Position.X + DX * StepSize;
        auto NewY = ParentActor.Position.Y + DY * StepSize;

        if (NewX < 0)
            NewX += Engine.GetCurrentMapArea().Size;
        if (NewY < 0)
            NewY += Engine.GetCurrentMapArea().Size;
        if (NewX >= Engine.GetCurrentMapArea().Size)
            NewX -= Engine.GetCurrentMapArea().Size;
        if (NewY >= Engine.GetCurrentMapArea().Size)
            NewY -= Engine.GetCurrentMapArea().Size;

        auto NewXRounded = int(std::round(NewX));
        auto NewYRounded = int(std::round(NewY));

        if (!Engine.GetCurrentMapArea().Tiles[NewXRounded][NewYRounded].MovementBlocked())
        {
            ParentActor.Position.X = NewX;
            ParentActor.Position.Y = NewY;
        }

        if (Engine.GetCurrentMapArea().Tiles[int(NewX)][int(NewY)].WarpToFloor != -1)
        {
            ParentActor.WorldMapCoord.Z = Engine.GetCurrentMapArea().Tiles[int(NewX)][int(NewY)].WarpToFloor;

            auto Angle = FacingAngle / 180.0f * (float)M_PI - (float)M_PI / 2 + 0 * (float)M_PI / 2;
            auto DX = -(float)std::cos(Angle) * StepMultiplier;
            auto DY = (float)std::sin(Angle) * StepMultiplier;

            NewX += DX * StepSize * 10;
            NewY += DY * StepSize * 10;

            ParentActor.Position.X = NewX;
            ParentActor.Position.Y = NewY;
        }
    }

    TickLastMove = Ticks();
}

}
