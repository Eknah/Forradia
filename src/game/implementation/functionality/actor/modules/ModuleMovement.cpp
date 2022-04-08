// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "ModuleMovement.h"
#include "../engine/Aliases.h"
#include "../engine/IEngine.h"
#include "implementation/functionality/actor/Actor.h"
#include "ModuleMovementData.h"

namespace Forradia {

ModuleMovement::ModuleMovement(const IEngine &engine_,
                                 Actor *parentActor_)
    : IModule(engine_, parentActor_) {
    GetParentActor().AddIfNotExists<ModuleMovementData>();
}

void ModuleMovement::ResetForNewFrame() {
  facingAngleRotated = *GetParentActor().GetModule<ModuleMovementData>().facingAngle;
}

void ModuleMovement::Update() {
  UpdateDirectionalMovement();
  UpdateDestinationMovement();
}

void ModuleMovement::UpdateRotation(float newFacingAngle) {
  *GetParentActor().GetModule<ModuleMovementData>().facingAngle = newFacingAngle;
}

void ModuleMovement::UpdateDirectionalMovement() {
  if (!(Ticks() > GetParentActor().GetModule<ModuleMovementData>().tickLastMove + GetParentActor().GetModule<ModuleMovementData>().moveSpeed &&
        (instruction.tryMoveForward || instruction.tryMoveRight ||
         instruction.tryMoveBack || instruction.tryMoveLeft)))
    return;

  GetParentActor().GetModule<ModuleMovementData>().isWalking = true;

  auto newX = GetParentActor().GetModule<ModuleMovementData>().position.x;
  auto newY = GetParentActor().GetModule<ModuleMovementData>().position.y;
  auto angle = 0.0f;
  auto piF = static_cast<float>(M_PI);

  if (instruction.tryMoveForward) {
    angle = *GetParentActor().GetModule<ModuleMovementData>().facingAngle / 180.0f * piF - piF / 2.0f +
            0.0f * piF / 2.0f;
  }

  if (instruction.tryMoveLeft) {
    angle = *GetParentActor().GetModule<ModuleMovementData>().facingAngle / 180.0f * piF - piF / 2.0f +
            1.0f * piF / 2.0f;
    *GetParentActor().GetModule<ModuleMovementData>().facingAngle = *GetParentActor().GetModule<ModuleMovementData>().facingAngle + 1 * 90.0f;
  }

  if (instruction.tryMoveBack) {
    angle = *GetParentActor().GetModule<ModuleMovementData>().facingAngle / 180.0f * piF - piF / 2.0f +
            2.0f * piF / 2.0f;
  }

  if (instruction.tryMoveRight) {
    angle = *GetParentActor().GetModule<ModuleMovementData>().facingAngle / 180.0f * piF - piF / 2.0f +
            3.0f * piF / 2.0f;
    *GetParentActor().GetModule<ModuleMovementData>().facingAngle = *GetParentActor().GetModule<ModuleMovementData>().facingAngle
            + 3.0f * 90.0f;
  }

  auto dx = -std::cos(angle) * GetParentActor().GetModule<ModuleMovementData>().stepMultiplier;
  auto dy = std::sin(angle) * GetParentActor().GetModule<ModuleMovementData>().stepMultiplier;

  newX += dx * GetParentActor().GetModule<ModuleMovementData>().stepSize;
  newY += dy * GetParentActor().GetModule<ModuleMovementData>().stepSize;

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
          .HasObjectWithFlag(ObjObstacle)
          && engine.GetCurrentMapArea()
          .tiles[newXRoundedI][newYRoundedI].groundType != GetId("GroundTypeWater")
          && !tileHasMob) {
      auto oldXI = static_cast<int>(GetParentActor().GetModule<ModuleMovementData>().position.x);
      auto oldYI = static_cast<int>(GetParentActor().GetModule<ModuleMovementData>().position.y);

    GetParentActor().GetModule<ModuleMovementData>().position.x = newXRounded;
    GetParentActor().GetModule<ModuleMovementData>().position.y = newYRounded;

    if (newXRoundedI != oldXI || newYRoundedI != oldYI) {
  engine.GetCurrentMapArea().tiles[newXRoundedI][newYRoundedI].actor
          = std::move(engine.GetCurrentMapArea().tiles[oldXI][oldYI].actor);
  engine.GetCurrentMapArea().tiles[oldXI][oldYI].actor = nullptr;
    }
  }

  if (engine.GetCurrentMapArea().tiles
          [static_cast<int>(newX)][static_cast<int>(newY)].properties.count("WarpToFloor") > 0) {
    auto angle = *GetParentActor().GetModule<ModuleMovementData>().facingAngle
            / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
    auto dx = -static_cast<float>(std::cos(angle)) * GetParentActor().GetModule<ModuleMovementData>().stepMultiplier;
    auto dy = static_cast<float>(std::sin(angle)) * GetParentActor().GetModule<ModuleMovementData>().stepMultiplier;

    auto newXOld = newX;
    auto newYOld = newY;

    newX += dx * GetParentActor().GetModule<ModuleMovementData>().stepSize * 10;
    newY += dy * GetParentActor().GetModule<ModuleMovementData>().stepSize * 10;

    auto oldXI = static_cast<int>(GetParentActor().GetModule<ModuleMovementData>().position.x);
    auto oldYI = static_cast<int>(GetParentActor().GetModule<ModuleMovementData>().position.y);

    GetParentActor().GetModule<ModuleMovementData>().position.x = newX;
    GetParentActor().GetModule<ModuleMovementData>().position.y = newY;

    auto coord = engine.GetCurrentMapArea().worldCoord;
    coord.z = std::stoi(engine.GetCurrentMapArea().tiles
            [static_cast<int>(newXOld)][static_cast<int>(newYOld)].properties.at("WarpToFloor"));

    engine.world->GetArea(coord)->tiles[newX][newY].actor
            = std::move(engine.GetCurrentMapArea().tiles[newXOld][newYOld].actor);
    engine.GetCurrentMapArea().tiles[newXOld][newYOld].actor = nullptr;

    GetParentActor().GetModule<ModuleMovementData>().worldMapCoord.z =
        std::stoi(engine.GetCurrentMapArea().tiles
            [static_cast<int>(newXOld)][static_cast<int>(newYOld)].properties.at("WarpToFloor"));
  }

  GetParentActor().GetModule<ModuleMovementData>().tickLastMove = Ticks();
}

void ModuleMovement::UpdateDestinationMovement() {
  if (!(Ticks() > GetParentActor().GetModule<ModuleMovementData>().tickLastMove + GetParentActor().GetModule<ModuleMovementData>().moveSpeed && GetParentActor().GetModule<ModuleMovementData>().moveDestination.x != -1 &&
        GetParentActor().GetModule<ModuleMovementData>().moveDestination.y != -1))
    return;

  auto dx = GetParentActor().GetModule<ModuleMovementData>().moveDestination.x - GetParentActor().GetModule<ModuleMovementData>().position.x;
  auto dy = GetParentActor().GetModule<ModuleMovementData>().moveDestination.y - GetParentActor().GetModule<ModuleMovementData>().position.y;
  auto absDx = std::abs(dx);
  auto absDy = std::abs(dy);
  auto piF = static_cast<float>(M_PI);

  if (absDx < GetParentActor().GetModule<ModuleMovementData>().stepMultiplier && absDy < GetParentActor().GetModule<ModuleMovementData>().stepMultiplier) {
    GetParentActor().GetModule<ModuleMovementData>().moveDestination = {-1, -1};
  } else {
    GetParentActor().GetModule<ModuleMovementData>().isWalking = true;
    *GetParentActor().GetModule<ModuleMovementData>().facingAngle
            = static_cast<float>(std::atan2(-dx, -dy)) / piF * 180.0f;

    auto angle = *GetParentActor().GetModule<ModuleMovementData>().facingAngle / 180.0f * piF - piF / 2 +
                 0 * piF / 2;
    auto dx = -static_cast<float>(std::cos(angle)) * GetParentActor().GetModule<ModuleMovementData>().stepMultiplier;
    auto dy = static_cast<float>(std::sin(angle)) * GetParentActor().GetModule<ModuleMovementData>().stepMultiplier;
    auto newX = GetParentActor().GetModule<ModuleMovementData>().position.x + dx * GetParentActor().GetModule<ModuleMovementData>().stepSize;
    auto newY = GetParentActor().GetModule<ModuleMovementData>().position.y + dy * GetParentActor().GetModule<ModuleMovementData>().stepSize;

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
            .HasObjectWithFlag(ObjObstacle)
            && engine.GetCurrentMapArea()
            .tiles[newXRoundedI][newYRoundedI].groundType != GetId("GroundTypeWater")
            && !tileHasMob) {
        auto oldXI = static_cast<int>(GetParentActor().GetModule<ModuleMovementData>().position.x);
        auto oldYI = static_cast<int>(GetParentActor().GetModule<ModuleMovementData>().position.y);

      GetParentActor().GetModule<ModuleMovementData>().position.x = newXRounded;
      GetParentActor().GetModule<ModuleMovementData>().position.y = newYRounded;

        if (newXRoundedI != oldXI || newYRoundedI != oldYI) {
      engine.GetCurrentMapArea().tiles[newXRoundedI][newYRoundedI].actor
              = std::move(engine.GetCurrentMapArea().tiles[oldXI][oldYI].actor);
      engine.GetCurrentMapArea().tiles[oldXI][oldYI].actor = nullptr;
        }
    }

    if (engine.GetCurrentMapArea().tiles
            [static_cast<int>(newX)][static_cast<int>(newY)].properties.count("WarpToFloor") > 0) {
        auto angle = *GetParentActor().GetModule<ModuleMovementData>().facingAngle
                / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
        auto dx = -static_cast<float>(std::cos(angle)) * GetParentActor().GetModule<ModuleMovementData>().stepMultiplier;
        auto dy = static_cast<float>(std::sin(angle)) * GetParentActor().GetModule<ModuleMovementData>().stepMultiplier;

        auto newXOld = newX;
        auto newYOld = newY;

        newX += dx * GetParentActor().GetModule<ModuleMovementData>().stepSize * 10;
        newY += dy * GetParentActor().GetModule<ModuleMovementData>().stepSize * 10;

        auto oldXI = static_cast<int>(GetParentActor().GetModule<ModuleMovementData>().position.x);
        auto oldYI = static_cast<int>(GetParentActor().GetModule<ModuleMovementData>().position.y);

        GetParentActor().GetModule<ModuleMovementData>().position.x = newX;
        GetParentActor().GetModule<ModuleMovementData>().position.y = newY;

        auto coord = engine.GetCurrentMapArea().worldCoord;
        coord.z = std::stoi(engine.GetCurrentMapArea().tiles
                [static_cast<int>(newXOld)][static_cast<int>(newYOld)].properties.at("WarpToFloor"));

        engine.world->GetArea(coord)->tiles[newX][newY].actor
                = std::move(engine.GetCurrentMapArea().tiles[newXOld][newYOld].actor);
        engine.GetCurrentMapArea().tiles[newXOld][newYOld].actor = nullptr;

        GetParentActor().GetModule<ModuleMovementData>().worldMapCoord.z =
            std::stoi(engine.GetCurrentMapArea().tiles
                [static_cast<int>(newXOld)][static_cast<int>(newYOld)].properties.at("WarpToFloor"));
    }
  }

  GetParentActor().GetModule<ModuleMovementData>().tickLastMove = Ticks();
}

}  // namespace Forradia
