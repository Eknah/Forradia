// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <algorithm>
#include <utility>
#include "cMobsEngine.h"
#include "../engine/cEngine.h"
#include "CommonExternal.h"

namespace Forradia {

void cMobsEngine::Update() {
  for (unsigned int I = 0; I < Engine.GetCurrentMapArea().ActorsMirror.size();
       I++) {
    if (I >= Engine.GetCurrentMapArea().ActorsMirror.size())
      break;

    if (typeid(*Engine.GetCurrentMapArea().ActorsMirror.at(I).get())
            != typeid(cMob)) continue;

    cMob& Mob = dynamic_cast<cMob&>(*Engine.GetCurrentMapArea().ActorsMirror.at(I).get().get());

    auto X = static_cast<int>(Mob.Position.X);
    auto Y = static_cast<int>(Mob.Position.Y);

    if (Ticks() > Mob.TickLastMove +
                      Mob.MoveSpeed) {
      Mob.TickLastMove = Ticks();

      if (Mob.MoveDestination.X == -1 ||
          Mob.MoveDestination.Y == -1) {
        auto DestinationX =
            Mob.Position.X +
            Random.Next() % 15 - Random.Next() % 15;
        auto DestinationY =
            Mob.Position.Y +
            Random.Next() % 15 - Random.Next() % 15;

        DestinationX =
                std::min(std::max(DestinationX, 0.0f),
                         static_cast<float>(Engine.WorldMap->
                                            MapAreaSize) - 1.0f);
        DestinationY =
                std::min(std::max(DestinationY, 0.0f),
                         static_cast<float>(Engine.WorldMap->
                                            MapAreaSize) - 1.0f);

        Mob.MoveDestination = {
            DestinationX, DestinationY};
      }

      auto DeltaX =
          Mob.MoveDestination.X -
          Mob.Position.X;
      auto DeltaY =
          Mob.MoveDestination.Y -
          Mob.Position.Y;
      auto Distance = std::sqrt(DeltaX * DeltaX + DeltaY * DeltaY);

      if (Distance < 1) {
        Mob.MoveDestination = {-1, -1};

        continue;
      }

      auto PiF = static_cast<float>(M_PI);

      Mob.FacingAngle =
          static_cast<float>(std::atan2(-DeltaX, -DeltaY)) / PiF * 180.0f;

      auto Angle = Mob.FacingAngle / 180.0f * PiF - PiF / 2 + PiF;
      auto DX = -std::cos(Angle) * Mob.StepMultiplier;
      auto DY = std::sin(Angle) * Mob.StepMultiplier;
      auto NewX =
          static_cast<float>(Mob.Position.X + DX * Mob.StepSize);
      auto NewY =
          static_cast<float>(Mob.Position.Y + DY * Mob.StepSize);
      auto NewXI = static_cast<int>(NewX);
      auto NewYI = static_cast<int>(NewY);
      auto OldXI = static_cast<int>(Mob.Position.X);
      auto OldYI = static_cast<int>(Mob.Position.Y);

      if (NewXI >= 0 && NewYI >= 0 && NewXI < Engine.WorldMap->MapAreaSize &&
          NewYI < Engine.WorldMap->MapAreaSize) {
        if (Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].GroundType !=
            GetId("GroundtypeWater")) {
          if (Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Actor == nullptr ||
              (NewXI == OldXI && NewYI == OldYI)) {
            Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Actor->Position = {
                NewX, NewY};

            if (NewXI != OldXI || NewYI != OldYI) {
              Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Actor =
                  std::move(Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Actor);
              Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Actor = nullptr;
            }

            Engine.GetCurrentMapArea().ActorsMirror.erase(
                Engine.GetCurrentMapArea().ActorsMirror.begin() + I);
            Engine.GetCurrentMapArea().ActorsMirror.push_back(
                std::ref(Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Actor));
          } else if (Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Actor !=
                         nullptr &&
                     (NewXI != OldXI || NewYI != OldYI)) {
            Mob.MoveDestination = {-1,
                                                                           -1};
          }
        } else {
          Mob.MoveDestination = {-1,
                                                                         -1};
        }
      } else {
        Mob.MoveDestination = {-1, -1};
      }
    }
  }
}

}  // namespace Forradia
