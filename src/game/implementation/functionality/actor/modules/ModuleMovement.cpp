// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "ModuleMovement.h"
#include "../engine/Aliases.h"
#include "../engine/iEngine.h"
#include "implementation/functionality/actor/Actor.h"
#include "ModuleMovementData.h"

namespace Forradia {

cModuleMovement::cModuleMovement(const iEngine &engine_,
                                 cActor *parentActor_)
    : iModule(engine_, parentActor_) {
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

  auto newX = GetParentActor().GetModule<cModuleMovementData>().position.x;
  auto newY = GetParentActor().GetModule<cModuleMovementData>().position.y;
  auto angle = 0.0f;
  auto piF = static_cast<float>(M_PI);

  if (instruction.tryMoveForward) {
    angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle / 180.0f * piF - piF / 2.0f +
            0.0f * piF / 2.0f;
  }

  if (instruction.tryMoveLeft) {
    angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle / 180.0f * piF - piF / 2.0f +
            1.0f * piF / 2.0f;
    *GetParentActor().GetModule<cModuleMovementData>().facingAngle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle + 1 * 90.0f;
  }

  if (instruction.tryMoveBack) {
    angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle / 180.0f * piF - piF / 2.0f +
            2.0f * piF / 2.0f;
  }

  if (instruction.tryMoveRight) {
    angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle / 180.0f * piF - piF / 2.0f +
            3.0f * piF / 2.0f;
    *GetParentActor().GetModule<cModuleMovementData>().facingAngle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle
            + 3.0f * 90.0f;
  }

  auto dx = -std::cos(angle) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;
  auto dy = std::sin(angle) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;

  newX += dx * GetParentActor().GetModule<cModuleMovementData>().stepSize;
  newY += dy * GetParentActor().GetModule<cModuleMovementData>().stepSize;

  if (newX < 0)
    newX += engine.GetCurrentMapArea().size;

  if (newY < 0)
    newY += engine.GetCurrentMapArea().size;

  if (newX >= engine.GetCurrentMapArea().size)
    newX -= engine.GetCurrentMapArea().size;

  if (newY >= engine.GetCurrentMapArea().size)
    newY -= engine.GetCurrentMapArea().size;

  auto newXRounded = newX;
  auto newYRounded = newY;

  auto newXRoundedI = static_cast<int>(newXRounded);
  auto newYRoundedI = static_cast<int>(newYRounded);

  auto tileHasMob = false;

  if (engine.GetCurrentMapArea()
          .tiles[newXRoundedI][newYRoundedI].actor != nullptr) {
    if (engine.GetCurrentMapArea()
            .tiles[newXRoundedI][newYRoundedI].actor->actorId != engine.GetPlayer().actorId)
        tileHasMob = true;
  }

  if (!engine.GetCurrentMapArea()
           .tiles[newXRoundedI][newYRoundedI]
          .HasObjectWithFlag(ObjectMovementBlock)
          && engine.GetCurrentMapArea()
          .tiles[newXRoundedI][newYRoundedI].groundType != GetId("GroundTypeWater")
          && !tileHasMob) {
      auto oldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.x);
      auto oldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.y);

    GetParentActor().GetModule<cModuleMovementData>().position.x = newXRounded;
    GetParentActor().GetModule<cModuleMovementData>().position.y = newYRounded;

    if (newXRoundedI != oldXI || newYRoundedI != oldYI) {
  engine.GetCurrentMapArea().tiles[newXRoundedI][newYRoundedI].actor
          = std::move(engine.GetCurrentMapArea().tiles[oldXI][oldYI].actor);
  engine.GetCurrentMapArea().tiles[oldXI][oldYI].actor = nullptr;
    }
  }

  if (engine.GetCurrentMapArea().tiles
          [static_cast<int>(newX)][static_cast<int>(newY)].properties.count("WarpToFloor") > 0) {
    auto angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle
            / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
    auto dx = -static_cast<float>(std::cos(angle)) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;
    auto dy = static_cast<float>(std::sin(angle)) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;

    auto newXOld = newX;
    auto newYOld = newY;

    newX += dx * GetParentActor().GetModule<cModuleMovementData>().stepSize * 10;
    newY += dy * GetParentActor().GetModule<cModuleMovementData>().stepSize * 10;

    auto oldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.x);
    auto oldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.y);

    GetParentActor().GetModule<cModuleMovementData>().position.x = newX;
    GetParentActor().GetModule<cModuleMovementData>().position.y = newY;

    auto coord = engine.GetCurrentMapArea().worldCoord;
    coord.z = std::stoi(engine.GetCurrentMapArea().tiles
            [static_cast<int>(newXOld)][static_cast<int>(newYOld)].properties.at("WarpToFloor"));

    engine.world->GetArea(coord)->tiles[newX][newY].actor
            = std::move(engine.GetCurrentMapArea().tiles[newXOld][newYOld].actor);
    engine.GetCurrentMapArea().tiles[newXOld][newYOld].actor = nullptr;

    GetParentActor().GetModule<cModuleMovementData>().worldMapCoord.z =
        std::stoi(engine.GetCurrentMapArea().tiles
            [static_cast<int>(newXOld)][static_cast<int>(newYOld)].properties.at("WarpToFloor"));
  }

  GetParentActor().GetModule<cModuleMovementData>().tickLastMove = Ticks();
}

void cModuleMovement::UpdateDestinationMovement() {
  if (!(Ticks() > GetParentActor().GetModule<cModuleMovementData>().tickLastMove + GetParentActor().GetModule<cModuleMovementData>().moveSpeed && GetParentActor().GetModule<cModuleMovementData>().moveDestination.x != -1 &&
        GetParentActor().GetModule<cModuleMovementData>().moveDestination.y != -1))
    return;

  auto dx = GetParentActor().GetModule<cModuleMovementData>().moveDestination.x - GetParentActor().GetModule<cModuleMovementData>().position.x;
  auto dy = GetParentActor().GetModule<cModuleMovementData>().moveDestination.y - GetParentActor().GetModule<cModuleMovementData>().position.y;
  auto absDx = std::abs(dx);
  auto absDy = std::abs(dy);
  auto piF = static_cast<float>(M_PI);

  if (absDx < GetParentActor().GetModule<cModuleMovementData>().stepMultiplier && absDy < GetParentActor().GetModule<cModuleMovementData>().stepMultiplier) {
    GetParentActor().GetModule<cModuleMovementData>().moveDestination = {-1, -1};
  } else {
    GetParentActor().GetModule<cModuleMovementData>().isWalking = true;
    *GetParentActor().GetModule<cModuleMovementData>().facingAngle
            = static_cast<float>(std::atan2(-dx, -dy)) / piF * 180.0f;

    auto angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle / 180.0f * piF - piF / 2 +
                 0 * piF / 2;
    auto dx = -static_cast<float>(std::cos(angle)) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;
    auto dy = static_cast<float>(std::sin(angle)) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;
    auto newX = GetParentActor().GetModule<cModuleMovementData>().position.x + dx * GetParentActor().GetModule<cModuleMovementData>().stepSize;
    auto newY = GetParentActor().GetModule<cModuleMovementData>().position.y + dy * GetParentActor().GetModule<cModuleMovementData>().stepSize;

    if (newX < 0)
      newX += engine.GetCurrentMapArea().size;
    if (newY < 0)
      newY += engine.GetCurrentMapArea().size;
    if (newX >= engine.GetCurrentMapArea().size)
      newX -= engine.GetCurrentMapArea().size;
    if (newY >= engine.GetCurrentMapArea().size)
      newY -= engine.GetCurrentMapArea().size;

      auto newXRounded = newX;
      auto newYRounded = newY;
      auto newXRoundedI = static_cast<int>(newXRounded);
      auto newYRoundedI = static_cast<int>(newYRounded);

      auto tileHasMob = false;

      if (engine.GetCurrentMapArea()
              .tiles[newXRoundedI][newYRoundedI].actor != nullptr) {
        if (engine.GetCurrentMapArea()
                .tiles[newXRoundedI][newYRoundedI].actor->actorId != engine.GetPlayer().actorId)
            tileHasMob = true;
      }

    if (!engine.GetCurrentMapArea()
             .tiles[newXRoundedI][newYRoundedI]
            .HasObjectWithFlag(ObjectMovementBlock)
            && engine.GetCurrentMapArea()
            .tiles[newXRoundedI][newYRoundedI].groundType != GetId("GroundTypeWater")
            && !tileHasMob) {
        auto oldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.x);
        auto oldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.y);

      GetParentActor().GetModule<cModuleMovementData>().position.x = newXRounded;
      GetParentActor().GetModule<cModuleMovementData>().position.y = newYRounded;

        if (newXRoundedI != oldXI || newYRoundedI != oldYI) {
      engine.GetCurrentMapArea().tiles[newXRoundedI][newYRoundedI].actor
              = std::move(engine.GetCurrentMapArea().tiles[oldXI][oldYI].actor);
      engine.GetCurrentMapArea().tiles[oldXI][oldYI].actor = nullptr;
        }
    }

    if (engine.GetCurrentMapArea().tiles
            [static_cast<int>(newX)][static_cast<int>(newY)].properties.count("WarpToFloor") > 0) {
        auto angle = *GetParentActor().GetModule<cModuleMovementData>().facingAngle
                / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
        auto dx = -static_cast<float>(std::cos(angle)) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;
        auto dy = static_cast<float>(std::sin(angle)) * GetParentActor().GetModule<cModuleMovementData>().stepMultiplier;

        auto newXOld = newX;
        auto newYOld = newY;

        newX += dx * GetParentActor().GetModule<cModuleMovementData>().stepSize * 10;
        newY += dy * GetParentActor().GetModule<cModuleMovementData>().stepSize * 10;

        auto oldXI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.x);
        auto oldYI = static_cast<int>(GetParentActor().GetModule<cModuleMovementData>().position.y);

        GetParentActor().GetModule<cModuleMovementData>().position.x = newX;
        GetParentActor().GetModule<cModuleMovementData>().position.y = newY;

        auto coord = engine.GetCurrentMapArea().worldCoord;
        coord.z = std::stoi(engine.GetCurrentMapArea().tiles
                [static_cast<int>(newXOld)][static_cast<int>(newYOld)].properties.at("WarpToFloor"));

        engine.world->GetArea(coord)->tiles[newX][newY].actor
                = std::move(engine.GetCurrentMapArea().tiles[newXOld][newYOld].actor);
        engine.GetCurrentMapArea().tiles[newXOld][newYOld].actor = nullptr;

        GetParentActor().GetModule<cModuleMovementData>().worldMapCoord.z =
            std::stoi(engine.GetCurrentMapArea().tiles
                [static_cast<int>(newXOld)][static_cast<int>(newYOld)].properties.at("WarpToFloor"));
    }
  }

  GetParentActor().GetModule<cModuleMovementData>().tickLastMove = Ticks();
}

}  // namespace Forradia
