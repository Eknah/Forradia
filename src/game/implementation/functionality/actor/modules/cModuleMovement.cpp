// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "cModuleMovement.h"
#include "../engine/Aliases.h"
#include "../engine/iEngine.h"
#include "implementation/functionality/actor/cActor.h"
#include "cModuleMovementData.h"

namespace Forradia {

cModuleMovement::cModuleMovement(const iEngine &Engine_,
                                 cActor *ParentActor_)
    : iModule(Engine_, ParentActor_) {
    GetParentActor().AddIfNotExists<cModuleMovementData>();
}

void cModuleMovement::ResetForNewFrame() {
  IsWalking = false;
  FacingAngleRotated = *GetParentActor().GetModule<cModuleMovementData>().FacingAngle;
}

void cModuleMovement::Update() {
  UpdateDirectionalMovement();
  UpdateDestinationMovement();
}

void cModuleMovement::UpdateRotation(float newFacingAngle) {
  *GetParentActor().GetModule<cModuleMovementData>().FacingAngle = newFacingAngle;
}

void cModuleMovement::UpdateDirectionalMovement() {
  if (!(Ticks() > GetParentActor().GetModule<cModuleMovementData>().TickLastMove + GetParentActor().GetModule<cModuleMovementData>().MoveSpeed &&
        (Instruction.TryMoveForward || Instruction.TryMoveRight ||
         Instruction.TryMoveBack || Instruction.TryMoveLeft)))
    return;

  IsWalking = true;

  auto NewX = GetParentActor().GetModule<cModuleMovementData>().Position.X;
  auto NewY = GetParentActor().GetModule<cModuleMovementData>().Position.Y;
  auto Angle = 0.0f;
  auto PiF = static_cast<float>(M_PI);

  if (Instruction.TryMoveForward) {
    Angle = *GetParentActor().GetModule<cModuleMovementData>().FacingAngle / 180.0f * PiF - PiF / 2.0f +
            0.0f * PiF / 2.0f;
  }

  if (Instruction.TryMoveLeft) {
    Angle = *GetParentActor().GetModule<cModuleMovementData>().FacingAngle / 180.0f * PiF - PiF / 2.0f +
            1.0f * PiF / 2.0f;
    *GetParentActor().GetModule<cModuleMovementData>().FacingAngle = *GetParentActor().GetModule<cModuleMovementData>().FacingAngle + 1 * 90.0f;
  }

  if (Instruction.TryMoveBack) {
    Angle = *GetParentActor().GetModule<cModuleMovementData>().FacingAngle / 180.0f * PiF - PiF / 2.0f +
            2.0f * PiF / 2.0f;
  }

  if (Instruction.TryMoveRight) {
    Angle = *GetParentActor().GetModule<cModuleMovementData>().FacingAngle / 180.0f * PiF - PiF / 2.0f +
            3.0f * PiF / 2.0f;
    *GetParentActor().GetModule<cModuleMovementData>().FacingAngle = *GetParentActor().GetModule<cModuleMovementData>().FacingAngle
            + 3.0f * 90.0f;
  }

  auto DX = -std::cos(Angle) * GetParentActor().GetModule<cModuleMovementData>().StepMultiplier;
  auto DY = std::sin(Angle) * GetParentActor().GetModule<cModuleMovementData>().StepMultiplier;

  NewX += DX * GetParentActor().GetModule<cModuleMovementData>().StepSize;
  NewY += DY * GetParentActor().GetModule<cModuleMovementData>().StepSize;

  if (NewX < 0)
    NewX += Engine.GetCurrentMapArea().Size;

  if (NewY < 0)
    NewY += Engine.GetCurrentMapArea().Size;

  if (NewX >= Engine.GetCurrentMapArea().Size)
    NewX -= Engine.GetCurrentMapArea().Size;

  if (NewY >= Engine.GetCurrentMapArea().Size)
    NewY -= Engine.GetCurrentMapArea().Size;

  auto NewXRounded = NewX;
  auto NewYRounded = NewY;

  auto NewXRoundedI = static_cast<int>(NewXRounded);
  auto NewYRoundedI = static_cast<int>(NewYRounded);

  auto TileHasMob = false;

  if (Engine.GetCurrentMapArea()
          .Tiles[NewXRoundedI][NewYRoundedI].Actor != nullptr) {
    if (Engine.GetCurrentMapArea()
            .Tiles[NewXRoundedI][NewYRoundedI].Actor->ActorId != Engine.GetPlayer().ActorId)
        TileHasMob = true;
  }

  if (!Engine.GetCurrentMapArea()
           .Tiles[NewXRoundedI][NewYRoundedI]
          .HasObjectWithFlag(ObjectMovementBlock)
          && Engine.GetCurrentMapArea()
          .Tiles[NewXRoundedI][NewYRoundedI].GroundType != GetId("GroundtypeWater")
          && !TileHasMob) {
      auto OldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.X);
      auto OldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.Y);

    GetParentActor().GetModule<cModuleMovementData>().Position.X = NewXRounded;
    GetParentActor().GetModule<cModuleMovementData>().Position.Y = NewYRounded;

    if (NewXRoundedI != OldXI || NewYRoundedI != OldYI) {
  Engine.GetCurrentMapArea().Tiles[NewXRoundedI][NewYRoundedI].Actor
          = std::move(Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Actor);
  Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Actor = nullptr;
    }
  }

  if (Engine.GetCurrentMapArea().Tiles
          [static_cast<int>(NewX)][static_cast<int>(NewY)].Properties.count("WarpToFloor") > 0) {
    auto Angle = *GetParentActor().GetModule<cModuleMovementData>().FacingAngle
            / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
    auto DX = -static_cast<float>(std::cos(Angle)) * GetParentActor().GetModule<cModuleMovementData>().StepMultiplier;
    auto DY = static_cast<float>(std::sin(Angle)) * GetParentActor().GetModule<cModuleMovementData>().StepMultiplier;

    auto NewXOld = NewX;
    auto NewYOld = NewY;

    NewX += DX * GetParentActor().GetModule<cModuleMovementData>().StepSize * 10;
    NewY += DY * GetParentActor().GetModule<cModuleMovementData>().StepSize * 10;

    auto OldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.X);
    auto OldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.Y);

    GetParentActor().GetModule<cModuleMovementData>().Position.X = NewX;
    GetParentActor().GetModule<cModuleMovementData>().Position.Y = NewY;

    auto coord = Engine.GetCurrentMapArea().WorldCoord;
    coord.Z = std::stoi(Engine.GetCurrentMapArea().Tiles
            [static_cast<int>(NewXOld)][static_cast<int>(NewYOld)].Properties.at("WarpToFloor"));

    Engine.World->GetArea(coord)->Tiles[NewX][NewY].Actor
            = std::move(Engine.GetCurrentMapArea().Tiles[NewXOld][NewYOld].Actor);
    Engine.GetCurrentMapArea().Tiles[NewXOld][NewYOld].Actor = nullptr;

    GetParentActor().GetModule<cModuleMovementData>().WorldMapCoord.Z =
        std::stoi(Engine.GetCurrentMapArea().Tiles
            [static_cast<int>(NewXOld)][static_cast<int>(NewYOld)].Properties.at("WarpToFloor"));
  }

  GetParentActor().GetModule<cModuleMovementData>().TickLastMove = Ticks();
}

void cModuleMovement::UpdateDestinationMovement() {
  if (!(Ticks() > GetParentActor().GetModule<cModuleMovementData>().TickLastMove + GetParentActor().GetModule<cModuleMovementData>().MoveSpeed && GetParentActor().GetModule<cModuleMovementData>().MoveDestination.X != -1 &&
        GetParentActor().GetModule<cModuleMovementData>().MoveDestination.Y != -1))
    return;

  auto DX = GetParentActor().GetModule<cModuleMovementData>().MoveDestination.X - GetParentActor().GetModule<cModuleMovementData>().Position.X;
  auto DY = GetParentActor().GetModule<cModuleMovementData>().MoveDestination.Y - GetParentActor().GetModule<cModuleMovementData>().Position.Y;
  auto AbsDX = std::abs(DX);
  auto AbsDY = std::abs(DY);
  auto PiF = static_cast<float>(M_PI);

  if (AbsDX < GetParentActor().GetModule<cModuleMovementData>().StepMultiplier && AbsDY < GetParentActor().GetModule<cModuleMovementData>().StepMultiplier) {
    GetParentActor().GetModule<cModuleMovementData>().MoveDestination = {-1, -1};
  } else {
    IsWalking = true;
    *GetParentActor().GetModule<cModuleMovementData>().FacingAngle
            = static_cast<float>(std::atan2(-DX, -DY)) / PiF * 180.0f;

    auto Angle = *GetParentActor().GetModule<cModuleMovementData>().FacingAngle / 180.0f * PiF - PiF / 2 +
                 0 * PiF / 2;
    auto DX = -static_cast<float>(std::cos(Angle)) * GetParentActor().GetModule<cModuleMovementData>().StepMultiplier;
    auto DY = static_cast<float>(std::sin(Angle)) * GetParentActor().GetModule<cModuleMovementData>().StepMultiplier;
    auto NewX = GetParentActor().GetModule<cModuleMovementData>().Position.X + DX * GetParentActor().GetModule<cModuleMovementData>().StepSize;
    auto NewY = GetParentActor().GetModule<cModuleMovementData>().Position.Y + DY * GetParentActor().GetModule<cModuleMovementData>().StepSize;

    if (NewX < 0)
      NewX += Engine.GetCurrentMapArea().Size;
    if (NewY < 0)
      NewY += Engine.GetCurrentMapArea().Size;
    if (NewX >= Engine.GetCurrentMapArea().Size)
      NewX -= Engine.GetCurrentMapArea().Size;
    if (NewY >= Engine.GetCurrentMapArea().Size)
      NewY -= Engine.GetCurrentMapArea().Size;

      auto NewXRounded = NewX;
      auto NewYRounded = NewY;
      auto NewXRoundedI = static_cast<int>(NewXRounded);
      auto NewYRoundedI = static_cast<int>(NewYRounded);

      auto TileHasMob = false;

      if (Engine.GetCurrentMapArea()
              .Tiles[NewXRoundedI][NewYRoundedI].Actor != nullptr) {
        if (Engine.GetCurrentMapArea()
                .Tiles[NewXRoundedI][NewYRoundedI].Actor->ActorId != Engine.GetPlayer().ActorId)
            TileHasMob = true;
      }

    if (!Engine.GetCurrentMapArea()
             .Tiles[NewXRoundedI][NewYRoundedI]
            .HasObjectWithFlag(ObjectMovementBlock)
            && Engine.GetCurrentMapArea()
            .Tiles[NewXRoundedI][NewYRoundedI].GroundType != GetId("GroundtypeWater")
            && !TileHasMob) {
        auto OldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.X);
        auto OldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.Y);

      GetParentActor().GetModule<cModuleMovementData>().Position.X = NewXRounded;
      GetParentActor().GetModule<cModuleMovementData>().Position.Y = NewYRounded;

        if (NewXRoundedI != OldXI || NewYRoundedI != OldYI) {
      Engine.GetCurrentMapArea().Tiles[NewXRoundedI][NewYRoundedI].Actor
              = std::move(Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Actor);
      Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Actor = nullptr;
        }
    }

    if (Engine.GetCurrentMapArea().Tiles
            [static_cast<int>(NewX)][static_cast<int>(NewY)].Properties.count("WarpToFloor") > 0) {
        auto Angle = *GetParentActor().GetModule<cModuleMovementData>().FacingAngle
                / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
        auto DX = -static_cast<float>(std::cos(Angle)) * GetParentActor().GetModule<cModuleMovementData>().StepMultiplier;
        auto DY = static_cast<float>(std::sin(Angle)) * GetParentActor().GetModule<cModuleMovementData>().StepMultiplier;

        auto NewXOld = NewX;
        auto NewYOld = NewY;

        NewX += DX * GetParentActor().GetModule<cModuleMovementData>().StepSize * 10;
        NewY += DY * GetParentActor().GetModule<cModuleMovementData>().StepSize * 10;

        auto OldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.X);
        auto OldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.Y);

        GetParentActor().GetModule<cModuleMovementData>().Position.X = NewX;
        GetParentActor().GetModule<cModuleMovementData>().Position.Y = NewY;

        auto coord = Engine.GetCurrentMapArea().WorldCoord;
        coord.Z = std::stoi(Engine.GetCurrentMapArea().Tiles
                [static_cast<int>(NewXOld)][static_cast<int>(NewYOld)].Properties.at("WarpToFloor"));

        Engine.World->GetArea(coord)->Tiles[NewX][NewY].Actor
                = std::move(Engine.GetCurrentMapArea().Tiles[NewXOld][NewYOld].Actor);
        Engine.GetCurrentMapArea().Tiles[NewXOld][NewYOld].Actor = nullptr;

        GetParentActor().GetModule<cModuleMovementData>().WorldMapCoord.Z =
            std::stoi(Engine.GetCurrentMapArea().Tiles
                [static_cast<int>(NewXOld)][static_cast<int>(NewYOld)].Properties.at("WarpToFloor"));
    }
  }

  GetParentActor().GetModule<cModuleMovementData>().TickLastMove = Ticks();
}

}  // namespace Forradia
