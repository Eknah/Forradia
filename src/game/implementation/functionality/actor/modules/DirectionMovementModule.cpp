// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "DirectionMovementModule.h"
#include "../engine/Aliases.h"
#include "../engine/IEngine.h"
#include "implementation/functionality/actor/Actor.h"
#include "MovementDataModule.h"

namespace Forradia {

DirectionMovementModule::DirectionMovementModule(const IEngine &_e,
                                 Actor *parentActor_)
    : IModule(_e, parentActor_) {
    GetParentActor().AddIfNotExists<MovementDataModule>();
}

void DirectionMovementModule::Update() {
    if (!(Ticks() > GetParentActor().GetModule<MovementDataModule>().tickLastMove + GetParentActor().GetModule<MovementDataModule>().moveSpeed &&
          (moveInstruction & DirForward || moveInstruction & DirRight ||
           moveInstruction & DirBack || moveInstruction & DirLeft)))
      return;

    GetParentActor().GetModule<MovementDataModule>().isWalking = true;

    auto newX = GetParentActor().GetModule<MovementDataModule>().position.x;
    auto newY = GetParentActor().GetModule<MovementDataModule>().position.y;
    auto angle = 0.0f;
    auto piF = static_cast<float>(M_PI);

    if (moveInstruction & DirForward) {
      angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle / 180.0f * piF - piF / 2.0f +
              0.0f * piF / 2.0f;
    }

    if (moveInstruction & DirLeft) {
      angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle / 180.0f * piF - piF / 2.0f +
              1.0f * piF / 2.0f;
      *GetParentActor().GetModule<MovementDataModule>().facingAngle = *GetParentActor().GetModule<MovementDataModule>().facingAngle + 1 * 90.0f;
    }

    if (moveInstruction & DirBack) {
      angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle / 180.0f * piF - piF / 2.0f +
              2.0f * piF / 2.0f;
    }

    if (moveInstruction & DirRight) {
      angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle / 180.0f * piF - piF / 2.0f +
              3.0f * piF / 2.0f;
      *GetParentActor().GetModule<MovementDataModule>().facingAngle = *GetParentActor().GetModule<MovementDataModule>().facingAngle
              + 3.0f * 90.0f;
    }

    auto dx = -std::cos(angle) * GetParentActor().GetModule<MovementDataModule>().stepMultiplier;
    auto dy = std::sin(angle) * GetParentActor().GetModule<MovementDataModule>().stepMultiplier;

    newX += dx * GetParentActor().GetModule<MovementDataModule>().stepSize;
    newY += dy * GetParentActor().GetModule<MovementDataModule>().stepSize;

    if (newX < 0)
      newX += e.GetCurrentMapArea().size;

    if (newY < 0)
      newY += e.GetCurrentMapArea().size;

    if (newX >= e.GetCurrentMapArea().size)
      newX -= e.GetCurrentMapArea().size;

    if (newY >= e.GetCurrentMapArea().size)
      newY -= e.GetCurrentMapArea().size;

    auto newXRounded = newX;
    auto newYRounded = newY;

    auto newXRoundedI = static_cast<int>(newXRounded);
    auto newYRoundedI = static_cast<int>(newYRounded);

    auto tileHasMob = false;

    if (e.GetCurrentMapArea()
            .tiles[newXRoundedI][newYRoundedI].actor != nullptr) {
      if (e.GetCurrentMapArea()
              .tiles[newXRoundedI][newYRoundedI].actor->actorId != e.GetPlayer().actorId)
          tileHasMob = true;
    }

    if (!e.GetCurrentMapArea()
             .tiles[newXRoundedI][newYRoundedI]
            .HasObjectWithFlag(ObjObstacle)
            && e.GetCurrentMapArea()
            .tiles[newXRoundedI][newYRoundedI].groundType != GetId("GroundTypeWater")
            && !tileHasMob) {
        auto oldXI = static_cast<int>(GetParentActor().GetModule<MovementDataModule>().position.x);
        auto oldYI = static_cast<int>(GetParentActor().GetModule<MovementDataModule>().position.y);

      GetParentActor().GetModule<MovementDataModule>().position.x = newXRounded;
      GetParentActor().GetModule<MovementDataModule>().position.y = newYRounded;

      if (newXRoundedI != oldXI || newYRoundedI != oldYI) {
    e.GetCurrentMapArea().tiles[newXRoundedI][newYRoundedI].actor
            = std::move(e.GetCurrentMapArea().tiles[oldXI][oldYI].actor);
    e.GetCurrentMapArea().tiles[oldXI][oldYI].actor = nullptr;
      }
    }

    if (e.GetCurrentMapArea().tiles
            [static_cast<int>(newX)][static_cast<int>(newY)].properties.count("WarpToFloor") > 0) {
      auto angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle
              / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
      auto dx = -static_cast<float>(std::cos(angle)) * GetParentActor().GetModule<MovementDataModule>().stepMultiplier;
      auto dy = static_cast<float>(std::sin(angle)) * GetParentActor().GetModule<MovementDataModule>().stepMultiplier;

      auto newXOld = newX;
      auto newYOld = newY;

      newX += dx * GetParentActor().GetModule<MovementDataModule>().stepSize * 10;
      newY += dy * GetParentActor().GetModule<MovementDataModule>().stepSize * 10;

      auto oldXI = static_cast<int>(GetParentActor().GetModule<MovementDataModule>().position.x);
      auto oldYI = static_cast<int>(GetParentActor().GetModule<MovementDataModule>().position.y);

      GetParentActor().GetModule<MovementDataModule>().position.x = newX;
      GetParentActor().GetModule<MovementDataModule>().position.y = newY;

      auto coord = e.GetCurrentMapArea().worldCoord;
      coord.z = std::stoi(e.GetCurrentMapArea().tiles
              [static_cast<int>(newXOld)][static_cast<int>(newYOld)].properties.at("WarpToFloor"));

      e.world->GetArea(coord)->tiles[newX][newY].actor
              = std::move(e.GetCurrentMapArea().tiles[newXOld][newYOld].actor);
      e.GetCurrentMapArea().tiles[newXOld][newYOld].actor = nullptr;

      GetParentActor().GetModule<MovementDataModule>().worldMapCoord.z =
          std::stoi(e.GetCurrentMapArea().tiles
              [static_cast<int>(newXOld)][static_cast<int>(newYOld)].properties.at("WarpToFloor"));
    }

    GetParentActor().GetModule<MovementDataModule>().tickLastMove = Ticks();
}



}  // namespace Forradia
