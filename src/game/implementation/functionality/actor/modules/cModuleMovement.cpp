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

  auto NewX = GetParentActor().GetModule<cModuleMovementData>().Position.x;
  auto NewY = GetParentActor().GetModule<cModuleMovementData>().Position.y;
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
    NewX += Engine.GetCurrentMapArea().size;

  if (NewY < 0)
    NewY += Engine.GetCurrentMapArea().size;

  if (NewX >= Engine.GetCurrentMapArea().size)
    NewX -= Engine.GetCurrentMapArea().size;

  if (NewY >= Engine.GetCurrentMapArea().size)
    NewY -= Engine.GetCurrentMapArea().size;

  auto NewXRounded = NewX;
  auto NewYRounded = NewY;

  auto NewXRoundedI = static_cast<int>(NewXRounded);
  auto NewYRoundedI = static_cast<int>(NewYRounded);

  auto TileHasMob = false;

  if (Engine.GetCurrentMapArea()
          .tiles[NewXRoundedI][NewYRoundedI].actor != nullptr) {
    if (Engine.GetCurrentMapArea()
            .tiles[NewXRoundedI][NewYRoundedI].actor->ActorId != Engine.GetPlayer().ActorId)
        TileHasMob = true;
  }

  if (!Engine.GetCurrentMapArea()
           .tiles[NewXRoundedI][NewYRoundedI]
          .HasObjectWithFlag(ObjectMovementBlock)
          && Engine.GetCurrentMapArea()
          .tiles[NewXRoundedI][NewYRoundedI].groundType != GetId("GroundtypeWater")
          && !TileHasMob) {
      auto OldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.x);
      auto OldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.y);

    GetParentActor().GetModule<cModuleMovementData>().Position.x = NewXRounded;
    GetParentActor().GetModule<cModuleMovementData>().Position.y = NewYRounded;

    if (NewXRoundedI != OldXI || NewYRoundedI != OldYI) {
  Engine.GetCurrentMapArea().tiles[NewXRoundedI][NewYRoundedI].actor
          = std::move(Engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor);
  Engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor = nullptr;
    }
  }

  if (Engine.GetCurrentMapArea().tiles
          [static_cast<int>(NewX)][static_cast<int>(NewY)].properties.count("WarpToFloor") > 0) {
    auto Angle = *GetParentActor().GetModule<cModuleMovementData>().FacingAngle
            / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
    auto DX = -static_cast<float>(std::cos(Angle)) * GetParentActor().GetModule<cModuleMovementData>().StepMultiplier;
    auto DY = static_cast<float>(std::sin(Angle)) * GetParentActor().GetModule<cModuleMovementData>().StepMultiplier;

    auto NewXOld = NewX;
    auto NewYOld = NewY;

    NewX += DX * GetParentActor().GetModule<cModuleMovementData>().StepSize * 10;
    NewY += DY * GetParentActor().GetModule<cModuleMovementData>().StepSize * 10;

    auto OldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.x);
    auto OldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.y);

    GetParentActor().GetModule<cModuleMovementData>().Position.x = NewX;
    GetParentActor().GetModule<cModuleMovementData>().Position.y = NewY;

    auto coord = Engine.GetCurrentMapArea().worldCoord;
    coord.z = std::stoi(Engine.GetCurrentMapArea().tiles
            [static_cast<int>(NewXOld)][static_cast<int>(NewYOld)].properties.at("WarpToFloor"));

    Engine.world->GetArea(coord)->tiles[NewX][NewY].actor
            = std::move(Engine.GetCurrentMapArea().tiles[NewXOld][NewYOld].actor);
    Engine.GetCurrentMapArea().tiles[NewXOld][NewYOld].actor = nullptr;

    GetParentActor().GetModule<cModuleMovementData>().WorldMapCoord.z =
        std::stoi(Engine.GetCurrentMapArea().tiles
            [static_cast<int>(NewXOld)][static_cast<int>(NewYOld)].properties.at("WarpToFloor"));
  }

  GetParentActor().GetModule<cModuleMovementData>().TickLastMove = Ticks();
}

void cModuleMovement::UpdateDestinationMovement() {
  if (!(Ticks() > GetParentActor().GetModule<cModuleMovementData>().TickLastMove + GetParentActor().GetModule<cModuleMovementData>().MoveSpeed && GetParentActor().GetModule<cModuleMovementData>().MoveDestination.x != -1 &&
        GetParentActor().GetModule<cModuleMovementData>().MoveDestination.y != -1))
    return;

  auto DX = GetParentActor().GetModule<cModuleMovementData>().MoveDestination.x - GetParentActor().GetModule<cModuleMovementData>().Position.x;
  auto DY = GetParentActor().GetModule<cModuleMovementData>().MoveDestination.y - GetParentActor().GetModule<cModuleMovementData>().Position.y;
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
    auto NewX = GetParentActor().GetModule<cModuleMovementData>().Position.x + DX * GetParentActor().GetModule<cModuleMovementData>().StepSize;
    auto NewY = GetParentActor().GetModule<cModuleMovementData>().Position.y + DY * GetParentActor().GetModule<cModuleMovementData>().StepSize;

    if (NewX < 0)
      NewX += Engine.GetCurrentMapArea().size;
    if (NewY < 0)
      NewY += Engine.GetCurrentMapArea().size;
    if (NewX >= Engine.GetCurrentMapArea().size)
      NewX -= Engine.GetCurrentMapArea().size;
    if (NewY >= Engine.GetCurrentMapArea().size)
      NewY -= Engine.GetCurrentMapArea().size;

      auto NewXRounded = NewX;
      auto NewYRounded = NewY;
      auto NewXRoundedI = static_cast<int>(NewXRounded);
      auto NewYRoundedI = static_cast<int>(NewYRounded);

      auto TileHasMob = false;

      if (Engine.GetCurrentMapArea()
              .tiles[NewXRoundedI][NewYRoundedI].actor != nullptr) {
        if (Engine.GetCurrentMapArea()
                .tiles[NewXRoundedI][NewYRoundedI].actor->ActorId != Engine.GetPlayer().ActorId)
            TileHasMob = true;
      }

    if (!Engine.GetCurrentMapArea()
             .tiles[NewXRoundedI][NewYRoundedI]
            .HasObjectWithFlag(ObjectMovementBlock)
            && Engine.GetCurrentMapArea()
            .tiles[NewXRoundedI][NewYRoundedI].groundType != GetId("GroundtypeWater")
            && !TileHasMob) {
        auto OldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.x);
        auto OldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.y);

      GetParentActor().GetModule<cModuleMovementData>().Position.x = NewXRounded;
      GetParentActor().GetModule<cModuleMovementData>().Position.y = NewYRounded;

        if (NewXRoundedI != OldXI || NewYRoundedI != OldYI) {
      Engine.GetCurrentMapArea().tiles[NewXRoundedI][NewYRoundedI].actor
              = std::move(Engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor);
      Engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor = nullptr;
        }
    }

    if (Engine.GetCurrentMapArea().tiles
            [static_cast<int>(NewX)][static_cast<int>(NewY)].properties.count("WarpToFloor") > 0) {
        auto Angle = *GetParentActor().GetModule<cModuleMovementData>().FacingAngle
                / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
        auto DX = -static_cast<float>(std::cos(Angle)) * GetParentActor().GetModule<cModuleMovementData>().StepMultiplier;
        auto DY = static_cast<float>(std::sin(Angle)) * GetParentActor().GetModule<cModuleMovementData>().StepMultiplier;

        auto NewXOld = NewX;
        auto NewYOld = NewY;

        NewX += DX * GetParentActor().GetModule<cModuleMovementData>().StepSize * 10;
        NewY += DY * GetParentActor().GetModule<cModuleMovementData>().StepSize * 10;

        auto OldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.x);
        auto OldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().Position.y);

        GetParentActor().GetModule<cModuleMovementData>().Position.x = NewX;
        GetParentActor().GetModule<cModuleMovementData>().Position.y = NewY;

        auto coord = Engine.GetCurrentMapArea().worldCoord;
        coord.z = std::stoi(Engine.GetCurrentMapArea().tiles
                [static_cast<int>(NewXOld)][static_cast<int>(NewYOld)].properties.at("WarpToFloor"));

        Engine.world->GetArea(coord)->tiles[NewX][NewY].actor
                = std::move(Engine.GetCurrentMapArea().tiles[NewXOld][NewYOld].actor);
        Engine.GetCurrentMapArea().tiles[NewXOld][NewYOld].actor = nullptr;

        GetParentActor().GetModule<cModuleMovementData>().WorldMapCoord.z =
            std::stoi(Engine.GetCurrentMapArea().tiles
                [static_cast<int>(NewXOld)][static_cast<int>(NewYOld)].properties.at("WarpToFloor"));
    }
  }

  GetParentActor().GetModule<cModuleMovementData>().TickLastMove = Ticks();
}

}  // namespace Forradia
