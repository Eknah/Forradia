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
       I < Engine.GetCurrentMapArea().mobActorsMirror.size(); I++) {
    if (I >= Engine.GetCurrentMapArea().mobActorsMirror.size())
      break;

    SPtr<cMob> MobPtr = std::dynamic_pointer_cast<cMob>(
        Engine.GetCurrentMapArea().mobActorsMirror.at(I).get());

    if (MobPtr == nullptr)
      continue;

    cActor &Actor =
        *Engine.GetCurrentMapArea().mobActorsMirror.at(I).get().get();

    if (Actor.actorId == Engine.GetPlayer().actorId)
      continue;

    cMob &Mob = *MobPtr;

    if (Mob.actorId == Engine.GetPlayer().actorId)
      continue;

    if (Ticks() > Mob.GetModule<cModuleMovementData>().tickLastMove + Mob.GetModule<cModuleMovementData>().moveSpeed) {
      Mob.GetModule<cModuleMovementData>().tickLastMove = Ticks();

      if (Mob.GetModule<cModuleMovementData>().moveDestination.x == -1 || Mob.GetModule<cModuleMovementData>().moveDestination.y == -1) {
        auto DestinationX =
            Mob.GetModule<cModuleMovementData>().position.x + Random.Next() % 15 - Random.Next() % 15;
        auto DestinationY =
            Mob.GetModule<cModuleMovementData>().position.y + Random.Next() % 15 - Random.Next() % 15;

        DestinationX =
            std::min(std::max(DestinationX, 0.0f),
                     static_cast<float>(Engine.world->mapAreaSize) - 1.0f);
        DestinationY =
            std::min(std::max(DestinationY, 0.0f),
                     static_cast<float>(Engine.world->mapAreaSize) - 1.0f);

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

      if (NewXI >= 0 && NewYI >= 0 && NewXI < Engine.world->mapAreaSize &&
          NewYI < Engine.world->mapAreaSize) {
        if (Engine.GetCurrentMapArea().tiles[NewXI][NewYI].groundType !=
            GetId("GroundTypeWater")) {
          if (Engine.GetCurrentMapArea().tiles[NewXI][NewYI].actor == nullptr ||
              (NewXI == OldXI && NewYI == OldYI)) {
            Engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor->GetModule<cModuleMovementData>().position = {
                NewX, NewY};

            if (NewXI != OldXI || NewYI != OldYI) {
              Engine.GetCurrentMapArea().tiles[NewXI][NewYI].actor = std::move(
                  Engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor);
              Engine.GetCurrentMapArea().tiles[OldXI][OldYI].actor = nullptr;
            }

            Engine.GetCurrentMapArea().mobActorsMirror.erase(
                Engine.GetCurrentMapArea().mobActorsMirror.begin() + I);
            Engine.GetCurrentMapArea().mobActorsMirror.push_back(
                std::ref(Engine.GetCurrentMapArea().tiles[NewXI][NewYI].actor));

          } else if (Engine.GetCurrentMapArea().tiles[NewXI][NewYI].actor !=
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
