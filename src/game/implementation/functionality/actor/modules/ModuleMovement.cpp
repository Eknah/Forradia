// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "ModuleMovement.h"
#include "../engine/Aliases.h"
#include "../engine/iEngine.h"
#include "implementation/functionality/actor/Actor.h"
#include "ModuleMovementData.h"

namespace Forradia {

cModuleMovement::cModuleMovement(const iEngine &Engine_,
                                 cActor *ParentActor_)
    : iModule(Engine_, ParentActor_) {
    GetParentActor().AddIfNotExists<cModuleMovementData>();
}

void cModuleMovement::ResetForNewFrame() {
  facingAngleRotated = *GetParentActor().GetModule<cModuleMovementData>().facingAngle;
}

void cModuleMovement::Update() {
  UpdateDirectionalMovement();
  UpdateDestinationMovement();
}

void cModuleMovement::UpdateRotation(float newFacingAngle) {
  *GetParentActor().GetModule<cModuleMovementData>().facingAngle = newFacingAngle;
}

void cModuleMovement::UpdateDirectionalMovement() {
  if (!(Ticks() > GetParentActor().GetModule<cModuleMovementData>().tickLastMove + GetParentActor().GetModule<cModuleMovementData>().moveSpeed &&
        (instruction.tryMoveForward || instruction.tryMoveRight ||
         instruction.tryMoveBack || instruction.tryMoveLeft)))
    return;

  GetParentActor().GetModule<cModuleMovementData>().isWalking = true;

  auto NewX = GetParentActor().GetModule<cModuleMovementData>().position.x;
  auto NewY = GetParentActor().GetModule<cModuleMovementData>().position.y;
  auto Angle = 0.0f;
  auto PiF = static_cast<float>(M_PI);

  if (instruction.tryMoveForward) {
    Angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle / 180.0f * PiF - PiF / 2.0f +
            0.0f * PiF / 2.0f;
  }

  if (instruction.tryMoveLeft) {
    Angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle / 180.0f * PiF - PiF / 2.0f +
            1.0f * PiF / 2.0f;
    *GetParentActor().GetModule<cModuleMovementData>().facingAngle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle + 1 * 90.0f;
  }

  if (instruction.tryMoveBack) {
    Angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle / 180.0f * PiF - PiF / 2.0f +
            2.0f * PiF / 2.0f;
  }

  if (instruction.tryMoveRight) {
    Angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle / 180.0f * PiF - PiF / 2.0f +
            3.0f * PiF / 2.0f;
    *GetParentActor().GetModule<cModuleMovementData>().facingAngle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle
            + 3.0f * 90.0f;
  }

  auto DX = -std::cos(Angle) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;
  auto DY = std::sin(Angle) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;

  NewX += DX * GetParentActor().GetModule<cModuleMovementData>().stepSize;
  NewY += DY * GetParentActor().GetModule<cModuleMovementData>().stepSize;

  if (NewX < 0)
    NewX += engine.GetCurrentMapArea().size;

  if (NewY < 0)
    NewY += engine.GetCurrentMapArea().size;

  if (NewX >= engine.GetCurrentMapArea().size)
    NewX -= engine.GetCurrentMapArea().size;

  if (NewY >= engine.GetCurrentMapArea().size)
    NewY -= engine.GetCurrentMapArea().size;

  auto NewXRounded = NewX;
  auto NewYRounded = NewY;

  auto NewXRoundedI = static_cast<int>(NewXRounded);
  auto NewYRoundedI = static_cast<int>(NewYRounded);

  auto TileHasMob = false;

  if (engine.GetCurrentMapArea()
          .tiles[NewXRoundedI][NewYRoundedI].actor != nullptr) {
    if (engine.GetCurrentMapArea()
            .tiles[NewXRoundedI][NewYRoundedI].actor->actorId != engine.GetPlayer().actorId)
        TileHasMob = true;
  }

  if (!engine.GetCurrentMapArea()
           .tiles[NewXRoundedI][NewYRoundedI]
          .HasObjectWithFlag(ObjectMovementBlock)
          && engine.GetCurrentMapArea()
          .tiles[NewXRoundedI][NewYRoundedI].groundType != GetId("GroundTypeWater")
          && !TileHasMob) {
      auto OldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.x);
      auto OldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.y);

    GetParentActor().GetModule<cModuleMovementData>().position.x = NewXRounded;
    GetParentActor().GetModule<cModuleMovementData>().position.y = NewYRounded;

    if (NewXRoundedI != OldXI || NewYRoundedI != OldYI) {
  engine.GetCurrentMapArea().tiles[NewXRoundedI][NewYRoundedI].actor
          = std::move(engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor);
  engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor = nullptr;
    }
  }

  if (engine.GetCurrentMapArea().tiles
          [static_cast<int>(NewX)][static_cast<int>(NewY)].properties.count("WarpToFloor") > 0) {
    auto Angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle
            / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
    auto DX = -static_cast<float>(std::cos(Angle)) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;
    auto DY = static_cast<float>(std::sin(Angle)) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;

    auto NewXOld = NewX;
    auto NewYOld = NewY;

    NewX += DX * GetParentActor().GetModule<cModuleMovementData>().stepSize * 10;
    NewY += DY * GetParentActor().GetModule<cModuleMovementData>().stepSize * 10;

    auto OldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.x);
    auto OldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.y);

    GetParentActor().GetModule<cModuleMovementData>().position.x = NewX;
    GetParentActor().GetModule<cModuleMovementData>().position.y = NewY;

    auto coord = engine.GetCurrentMapArea().worldCoord;
    coord.z = std::stoi(engine.GetCurrentMapArea().tiles
            [static_cast<int>(NewXOld)][static_cast<int>(NewYOld)].properties.at("WarpToFloor"));

    engine.world->GetArea(coord)->tiles[NewX][NewY].actor
            = std::move(engine.GetCurrentMapArea().tiles[NewXOld][NewYOld].actor);
    engine.GetCurrentMapArea().tiles[NewXOld][NewYOld].actor = nullptr;

    GetParentActor().GetModule<cModuleMovementData>().worldMapCoord.z =
        std::stoi(engine.GetCurrentMapArea().tiles
            [static_cast<int>(NewXOld)][static_cast<int>(NewYOld)].properties.at("WarpToFloor"));
  }

  GetParentActor().GetModule<cModuleMovementData>().tickLastMove = Ticks();
}

void cModuleMovement::UpdateDestinationMovement() {
  if (!(Ticks() > GetParentActor().GetModule<cModuleMovementData>().tickLastMove + GetParentActor().GetModule<cModuleMovementData>().moveSpeed && GetParentActor().GetModule<cModuleMovementData>().moveDestination.x != -1 &&
        GetParentActor().GetModule<cModuleMovementData>().moveDestination.y != -1))
    return;

  auto DX = GetParentActor().GetModule<cModuleMovementData>().moveDestination.x - GetParentActor().GetModule<cModuleMovementData>().position.x;
  auto DY = GetParentActor().GetModule<cModuleMovementData>().moveDestination.y - GetParentActor().GetModule<cModuleMovementData>().position.y;
  auto AbsDX = std::abs(DX);
  auto AbsDY = std::abs(DY);
  auto PiF = static_cast<float>(M_PI);

  if (AbsDX < GetParentActor().GetModule<cModuleMovementData>().stepMultiplier && AbsDY < GetParentActor().GetModule<cModuleMovementData>().stepMultiplier) {
    GetParentActor().GetModule<cModuleMovementData>().moveDestination = {-1, -1};
  } else {
    GetParentActor().GetModule<cModuleMovementData>().isWalking = true;
    *GetParentActor().GetModule<cModuleMovementData>().facingAngle
            = static_cast<float>(std::atan2(-DX, -DY)) / PiF * 180.0f;

    auto Angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle / 180.0f * PiF - PiF / 2 +
                 0 * PiF / 2;
    auto DX = -static_cast<float>(std::cos(Angle)) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;
    auto DY = static_cast<float>(std::sin(Angle)) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;
    auto NewX = GetParentActor().GetModule<cModuleMovementData>().position.x + DX * GetParentActor().GetModule<cModuleMovementData>().stepSize;
    auto NewY = GetParentActor().GetModule<cModuleMovementData>().position.y + DY * GetParentActor().GetModule<cModuleMovementData>().stepSize;

    if (NewX < 0)
      NewX += engine.GetCurrentMapArea().size;
    if (NewY < 0)
      NewY += engine.GetCurrentMapArea().size;
    if (NewX >= engine.GetCurrentMapArea().size)
      NewX -= engine.GetCurrentMapArea().size;
    if (NewY >= engine.GetCurrentMapArea().size)
      NewY -= engine.GetCurrentMapArea().size;

      auto NewXRounded = NewX;
      auto NewYRounded = NewY;
      auto NewXRoundedI = static_cast<int>(NewXRounded);
      auto NewYRoundedI = static_cast<int>(NewYRounded);

      auto TileHasMob = false;

      if (engine.GetCurrentMapArea()
              .tiles[NewXRoundedI][NewYRoundedI].actor != nullptr) {
        if (engine.GetCurrentMapArea()
                .tiles[NewXRoundedI][NewYRoundedI].actor->actorId != engine.GetPlayer().actorId)
            TileHasMob = true;
      }

    if (!engine.GetCurrentMapArea()
             .tiles[NewXRoundedI][NewYRoundedI]
            .HasObjectWithFlag(ObjectMovementBlock)
            && engine.GetCurrentMapArea()
            .tiles[NewXRoundedI][NewYRoundedI].groundType != GetId("GroundTypeWater")
            && !TileHasMob) {
        auto OldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.x);
        auto OldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.y);

      GetParentActor().GetModule<cModuleMovementData>().position.x = NewXRounded;
      GetParentActor().GetModule<cModuleMovementData>().position.y = NewYRounded;

        if (NewXRoundedI != OldXI || NewYRoundedI != OldYI) {
      engine.GetCurrentMapArea().tiles[NewXRoundedI][NewYRoundedI].actor
              = std::move(engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor);
      engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor = nullptr;
        }
    }

    if (engine.GetCurrentMapArea().tiles
            [static_cast<int>(NewX)][static_cast<int>(NewY)].properties.count("WarpToFloor") > 0) {
        auto Angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle
                / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
        auto DX = -static_cast<float>(std::cos(Angle)) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;
        auto DY = static_cast<float>(std::sin(Angle)) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;

        auto NewXOld = NewX;
        auto NewYOld = NewY;

        NewX += DX * GetParentActor().GetModule<cModuleMovementData>().stepSize * 10;
        NewY += DY * GetParentActor().GetModule<cModuleMovementData>().stepSize * 10;

        auto OldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.x);
        auto OldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.y);

        GetParentActor().GetModule<cModuleMovementData>().position.x = NewX;
        GetParentActor().GetModule<cModuleMovementData>().position.y = NewY;

        auto coord = engine.GetCurrentMapArea().worldCoord;
        coord.z = std::stoi(engine.GetCurrentMapArea().tiles
                [static_cast<int>(NewXOld)][static_cast<int>(NewYOld)].properties.at("WarpToFloor"));

        engine.world->GetArea(coord)->tiles[NewX][NewY].actor
                = std::move(engine.GetCurrentMapArea().tiles[NewXOld][NewYOld].actor);
        engine.GetCurrentMapArea().tiles[NewXOld][NewYOld].actor = nullptr;

        GetParentActor().GetModule<cModuleMovementData>().worldMapCoord.z =
            std::stoi(engine.GetCurrentMapArea().tiles
                [static_cast<int>(NewXOld)][static_cast<int>(NewYOld)].properties.at("WarpToFloor"));
    }
  }

  GetParentActor().GetModule<cModuleMovementData>().tickLastMove = Ticks();
}

}  // namespace Forradia
