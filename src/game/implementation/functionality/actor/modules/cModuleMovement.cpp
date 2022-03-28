// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cModuleMovement.h"
#include "../engine/Aliases.h"
#include "../engine/iEngine.h"
#include "implementation/functionality/actor/cActor.h"

namespace Forradia {

void cModuleMovement::ResetForNewFrame() {
  IsWalking = false;
  FacingAngleRotated = FacingAngle;
}

void cModuleMovement::Update() {
  UpdateDirectionalMovement();
  UpdateDestinationMovement();
}

void cModuleMovement::UpdateRotation(float newFacingAngle) {
  FacingAngle = newFacingAngle;
}

void cModuleMovement::UpdateDirectionalMovement() {
  if (!(Ticks() > TickLastMove + MoveSpeed &&
        (Instruction.TryMoveForward || Instruction.TryMoveRight ||
         Instruction.TryMoveBack || Instruction.TryMoveLeft)))
    return;

  IsWalking = true;

  auto NewX = GetParentActor().Position.X;
  auto NewY = GetParentActor().Position.Y;
  auto Angle = 0.0f;
  auto PiF = static_cast<float>(M_PI);

  if (Instruction.TryMoveForward) {
    Angle = FacingAngle / 180.0f * PiF - PiF / 2.0f +
            0.0f * PiF / 2.0f;
  }

  if (Instruction.TryMoveLeft) {
    Angle = FacingAngle / 180.0f * PiF - PiF / 2.0f +
            1.0f * PiF / 2.0f;
    FacingAngleRotated = FacingAngle + 1 * 90.0f;
  }

  if (Instruction.TryMoveBack) {
    Angle = FacingAngle / 180.0f * PiF - PiF / 2.0f +
            2.0f * PiF / 2.0f;
  }

  if (Instruction.TryMoveRight) {
    Angle = FacingAngle / 180.0f * PiF - PiF / 2.0f +
            3.0f * PiF / 2.0f;
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

  auto NewXRounded = static_cast<int>(std::round(NewX));
  auto NewYRounded = static_cast<int>(std::round(NewY));

  if (!Engine.GetCurrentMapArea()
           .Tiles[NewXRounded][NewYRounded]
           .MovementBlocked()) {
    GetParentActor().Position.X = NewX;
    GetParentActor().Position.Y = NewY;
  }

  if (Engine.GetCurrentMapArea().Tiles[static_cast<int>(NewX)][static_cast<int>(NewY)].WarpToFloor !=
      -1) {
    GetParentActor().WorldMapCoord.Z =
        Engine.GetCurrentMapArea().Tiles[static_cast<int>(NewX)][static_cast<int>(NewY)].WarpToFloor;

    auto Angle = FacingAngle / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
    auto DX = -static_cast<float>(std::cos(Angle)) * StepMultiplier;
    auto DY = static_cast<float>(std::sin(Angle)) * StepMultiplier;

    NewX += DX * StepSize * 10;
    NewY += DY * StepSize * 10;

    GetParentActor().Position.X = NewX;
    GetParentActor().Position.Y = NewY;
  }

  TickLastMove = Ticks();
}

void cModuleMovement::UpdateDestinationMovement() {
  if (!(Ticks() > TickLastMove + MoveSpeed && MoveDestination.X != -1 &&
        MoveDestination.Y != -1))
    return;

  auto DX = MoveDestination.X - GetParentActor().Position.X;
  auto DY = MoveDestination.Y - GetParentActor().Position.Y;
  auto AbsDX = std::abs(DX);
  auto AbsDY = std::abs(DY);
  auto PiF = static_cast<float>(M_PI);

  if (AbsDX < StepMultiplier && AbsDY < StepMultiplier) {
    MoveDestination = {-1, -1};
  } else {
    IsWalking = true;
    FacingAngle = (float)std::atan2(-DX, -DY) / PiF * 180.0f;

    auto Angle = FacingAngle / 180.0f * PiF - PiF / 2 +
                 0 * PiF / 2;
    auto DX = -(float)std::cos(Angle) * StepMultiplier;
    auto DY = (float)std::sin(Angle) * StepMultiplier;
    auto NewX = GetParentActor().Position.X + DX * StepSize;
    auto NewY = GetParentActor().Position.Y + DY * StepSize;

    if (NewX < 0)
      NewX += Engine.GetCurrentMapArea().Size;
    if (NewY < 0)
      NewY += Engine.GetCurrentMapArea().Size;
    if (NewX >= Engine.GetCurrentMapArea().Size)
      NewX -= Engine.GetCurrentMapArea().Size;
    if (NewY >= Engine.GetCurrentMapArea().Size)
      NewY -= Engine.GetCurrentMapArea().Size;

    auto NewXRounded = static_cast<int>(std::round(NewX));
    auto NewYRounded = static_cast<int>(std::round(NewY));

    if (!Engine.GetCurrentMapArea()
             .Tiles[NewXRounded][NewYRounded]
             .MovementBlocked()) {
      GetParentActor().Position.X = NewX;
      GetParentActor().Position.Y = NewY;
    }

    if (Engine.GetCurrentMapArea().Tiles[static_cast<int>(NewX)][static_cast<int>(NewY)].WarpToFloor !=
        -1) {
      GetParentActor().WorldMapCoord.Z =
          Engine.GetCurrentMapArea().Tiles[static_cast<int>(NewX)][static_cast<int>(NewY)].WarpToFloor;

      auto Angle = FacingAngle / 180.0f * PiF - PiF / 2 +
                   0 * PiF / 2;
      auto DX = -static_cast<float>(std::cos(Angle)) * StepMultiplier;
      auto DY = static_cast<float>(std::sin(Angle)) * StepMultiplier;

      NewX += DX * StepSize * 10;
      NewY += DY * StepSize * 10;

      GetParentActor().Position.X = NewX;
      GetParentActor().Position.Y = NewY;
    }
  }

  TickLastMove = Ticks();
}

}  // namespace Forradia
