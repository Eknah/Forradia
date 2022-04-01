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
       I < Engine.GetCurrentMapArea().MobActorsMirror.size(); I++) {
    if (I >= Engine.GetCurrentMapArea().MobActorsMirror.size())
      break;

    SPtr<cMob> MobPtr = std::dynamic_pointer_cast<cMob>(
        Engine.GetCurrentMapArea().MobActorsMirror.at(I).get());

    if (MobPtr == nullptr)
      continue;

    cActor &Actor =
        *Engine.GetCurrentMapArea().MobActorsMirror.at(I).get().get();

    if (Actor.ActorId == Engine.GetPlayer().ActorId)
      continue;

    cMob &Mob = *MobPtr;

    if (Mob.ActorId == Engine.GetPlayer().ActorId)
      continue;

    if (Ticks() > Mob.GetModule<cModuleMovementData>().TickLastMove + Mob.GetModule<cModuleMovementData>().MoveSpeed) {
      Mob.GetModule<cModuleMovementData>().TickLastMove = Ticks();

      if (Mob.GetModule<cModuleMovementData>().MoveDestination.X == -1 || Mob.GetModule<cModuleMovementData>().MoveDestination.Y == -1) {
        auto DestinationX =
            Mob.GetModule<cModuleMovementData>().Position.X + Random.Next() % 15 - Random.Next() % 15;
        auto DestinationY =
            Mob.GetModule<cModuleMovementData>().Position.Y + Random.Next() % 15 - Random.Next() % 15;

        DestinationX =
            std::min(std::max(DestinationX, 0.0f),
                     static_cast<float>(Engine.World->MapAreaSize) - 1.0f);
        DestinationY =
            std::min(std::max(DestinationY, 0.0f),
                     static_cast<float>(Engine.World->MapAreaSize) - 1.0f);

        Mob.GetModule<cModuleMovementData>().MoveDestination = {DestinationX, DestinationY};
      }

      auto DeltaX = Mob.GetModule<cModuleMovementData>().MoveDestination.X - Mob.GetModule<cModuleMovementData>().Position.X;
      auto DeltaY = Mob.GetModule<cModuleMovementData>().MoveDestination.Y - Mob.GetModule<cModuleMovementData>().Position.Y;
      auto Distance = std::sqrt(DeltaX * DeltaX + DeltaY * DeltaY);

      if (Distance < 1) {
        Mob.GetModule<cModuleMovementData>().MoveDestination = {-1, -1};

        continue;
      }

      auto PiF = static_cast<float>(M_PI);

      *Mob.GetModule<cModuleMovementData>().FacingAngle =
          static_cast<float>(std::atan2(-DeltaX, -DeltaY)) / PiF * 180.0f;

      auto Angle = *Mob.GetModule<cModuleMovementData>().FacingAngle / 180.0f * PiF - PiF / 2 + PiF;
      auto DX = -std::cos(Angle) * Mob.GetModule<cModuleMovementData>().StepMultiplier;
      auto DY = std::sin(Angle) * Mob.GetModule<cModuleMovementData>().StepMultiplier;
      auto NewX = static_cast<float>(Mob.GetModule<cModuleMovementData>().Position.X + DX * Mob.GetModule<cModuleMovementData>().StepSize);
      auto NewY = static_cast<float>(Mob.GetModule<cModuleMovementData>().Position.Y + DY * Mob.GetModule<cModuleMovementData>().StepSize);
      auto NewXI = static_cast<int>(NewX);
      auto NewYI = static_cast<int>(NewY);
      auto OldXI = static_cast<int>(Mob.GetModule<cModuleMovementData>().Position.X);
      auto OldYI = static_cast<int>(Mob.GetModule<cModuleMovementData>().Position.Y);

      if (NewXI >= 0 && NewYI >= 0 && NewXI < Engine.World->MapAreaSize &&
          NewYI < Engine.World->MapAreaSize) {
        if (Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].GroundType !=
            GetId("GroundtypeWater")) {
          if (Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Actor == nullptr ||
              (NewXI == OldXI && NewYI == OldYI)) {
            Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Actor->GetModule<cModuleMovementData>().Position = {
                NewX, NewY};

            if (NewXI != OldXI || NewYI != OldYI) {
              Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Actor = std::move(
                  Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Actor);
              Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Actor = nullptr;
            }

            Engine.GetCurrentMapArea().MobActorsMirror.erase(
                Engine.GetCurrentMapArea().MobActorsMirror.begin() + I);
            Engine.GetCurrentMapArea().MobActorsMirror.push_back(
                std::ref(Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Actor));

          } else if (Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Actor !=
                         nullptr &&
                     (NewXI != OldXI || NewYI != OldYI)) {
            Mob.GetModule<cModuleMovementData>().MoveDestination = {-1, -1};
          }

        } else {
          Mob.GetModule<cModuleMovementData>().MoveDestination = {-1, -1};
        }

      } else {
        Mob.GetModule<cModuleMovementData>().MoveDestination = {-1, -1};
      }
    }
  }
}

}  // namespace Forradia
