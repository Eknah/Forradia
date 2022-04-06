// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <algorithm>
#include <utility>
#include "cMobsEngine.h"
#include "../engine/cEngine.h"
#include "implementation/functionality/actor/modules/cModuleMovementData.h"

namespace Forradia {

void cMobsEngine::Update() {
  for (unsigned int I = 0;
       I < engine.GetCurrentMapArea().mobActorsMirror.size(); I++) {
    if (I >= engine.GetCurrentMapArea().mobActorsMirror.size())
      break;

    SPtr<cMob> MobPtr = std::dynamic_pointer_cast<cMob>(
        engine.GetCurrentMapArea().mobActorsMirror.at(I).get());

    if (MobPtr == nullptr)
      continue;

    cActor &Actor =
        *engine.GetCurrentMapArea().mobActorsMirror.at(I).get().get();

    if (Actor.actorId == engine.GetPlayer().actorId)
      continue;

    cMob &Mob = *MobPtr;

    if (Mob.actorId == engine.GetPlayer().actorId)
      continue;

    if (Ticks() > Mob.GetModule<cModuleMovementData>().tickLastMove + Mob.GetModule<cModuleMovementData>().moveSpeed) {
      Mob.GetModule<cModuleMovementData>().tickLastMove = Ticks();

      if (Mob.GetModule<cModuleMovementData>().moveDestination.x == -1 || Mob.GetModule<cModuleMovementData>().moveDestination.y == -1) {
        auto DestinationX =
            Mob.GetModule<cModuleMovementData>().position.x + random.Next() % 15 - random.Next() % 15;
        auto DestinationY =
            Mob.GetModule<cModuleMovementData>().position.y + random.Next() % 15 - random.Next() % 15;

        DestinationX =
            std::min(std::max(DestinationX, 0.0f),
                     static_cast<float>(engine.world->mapAreaSize) - 1.0f);
        DestinationY =
            std::min(std::max(DestinationY, 0.0f),
                     static_cast<float>(engine.world->mapAreaSize) - 1.0f);

        Mob.GetModule<cModuleMovementData>().moveDestination = {DestinationX, DestinationY};
      }

      auto DeltaX = Mob.GetModule<cModuleMovementData>().moveDestination.x - Mob.GetModule<cModuleMovementData>().position.x;
      auto DeltaY = Mob.GetModule<cModuleMovementData>().moveDestination.y - Mob.GetModule<cModuleMovementData>().position.y;
      auto Distance = std::sqrt(DeltaX * DeltaX + DeltaY * DeltaY);

      if (Distance < 1) {
        Mob.GetModule<cModuleMovementData>().moveDestination = {-1, -1};

        continue;
      }

      auto PiF = static_cast<float>(M_PI);

      *Mob.GetModule<cModuleMovementData>().facingAngle =
          static_cast<float>(std::atan2(-DeltaX, -DeltaY)) / PiF * 180.0f;

      auto Angle = *Mob.GetModule<cModuleMovementData>().facingAngle / 180.0f * PiF - PiF / 2 + PiF;
      auto DX = -std::cos(Angle) * Mob.GetModule<cModuleMovementData>().stepMultiplier;
      auto DY = std::sin(Angle) * Mob.GetModule<cModuleMovementData>().stepMultiplier;
      auto NewX = static_cast<float>(Mob.GetModule<cModuleMovementData>().position.x + DX * Mob.GetModule<cModuleMovementData>().stepSize);
      auto NewY = static_cast<float>(Mob.GetModule<cModuleMovementData>().position.y + DY * Mob.GetModule<cModuleMovementData>().stepSize);
      auto NewXI = static_cast<int>(NewX);
      auto NewYI = static_cast<int>(NewY);
      auto OldXI = static_cast<int>(Mob.GetModule<cModuleMovementData>().position.x);
      auto OldYI = static_cast<int>(Mob.GetModule<cModuleMovementData>().position.y);

      if (NewXI >= 0 && NewYI >= 0 && NewXI < engine.world->mapAreaSize &&
          NewYI < engine.world->mapAreaSize) {
        if (engine.GetCurrentMapArea().tiles[NewXI][NewYI].groundType !=
            GetId("GroundTypeWater")) {
          if (engine.GetCurrentMapArea().tiles[NewXI][NewYI].actor == nullptr ||
              (NewXI == OldXI && NewYI == OldYI)) {
            engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor->GetModule<cModuleMovementData>().position = {
                NewX, NewY};

            if (NewXI != OldXI || NewYI != OldYI) {
              engine.GetCurrentMapArea().tiles[NewXI][NewYI].actor = std::move(
                  engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor);
              engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor = nullptr;
            }

            engine.GetCurrentMapArea().mobActorsMirror.erase(
                engine.GetCurrentMapArea().mobActorsMirror.begin() + I);
            engine.GetCurrentMapArea().mobActorsMirror.push_back(
                std::ref(engine.GetCurrentMapArea().tiles[NewXI][NewYI].actor));

          } else if (engine.GetCurrentMapArea().tiles[NewXI][NewYI].actor !=
                         nullptr &&
                     (NewXI != OldXI || NewYI != OldYI)) {
            Mob.GetModule<cModuleMovementData>().moveDestination = {-1, -1};
          }

        } else {
          Mob.GetModule<cModuleMovementData>().moveDestination = {-1, -1};
        }

      } else {
        Mob.GetModule<cModuleMovementData>().moveDestination = {-1, -1};
      }
    }
  }
}

}  // namespace Forradia
