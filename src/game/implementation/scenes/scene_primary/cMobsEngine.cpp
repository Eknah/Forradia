// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <algorithm>
#include <utility>
#include "cMobsEngine.h"
#include "../engine/cEngine.h"
#include "CommonExternal.h"

namespace Forradia {

void cMobsEngine::Update() {
  for (unsigned int I = 0; I < Engine.GetCurrentMapArea().MobsMirror.size();
       I++) {
    if (I >= Engine.GetCurrentMapArea().MobsMirror.size())
      break;

    auto X = int(Engine.GetCurrentMapArea().MobsMirror.at(I).get()->Position.X);
    auto Y = int(Engine.GetCurrentMapArea().MobsMirror.at(I).get()->Position.Y);

    if (Ticks() > Engine.GetCurrentMapArea().Tiles[X][Y].Mob->TickLastMove +
                      Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveSpeed) {
      Engine.GetCurrentMapArea().Tiles[X][Y].Mob->TickLastMove = Ticks();

      if (Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination.X == -1 ||
          Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination.Y == -1) {
        auto DestinationX =
            Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.X +
            Random.Next() % 15 - Random.Next() % 15;
        auto DestinationY =
            Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.Y +
            Random.Next() % 15 - Random.Next() % 15;

        DestinationX = std::min(std::max(DestinationX, 0.0f),
                                static_cast<float>(Engine.WorldMap->MapAreaSize) - 1.0f);
        DestinationY = std::min(std::max(DestinationY, 0.0f),
                                static_cast<float>(Engine.WorldMap->MapAreaSize) - 1.0f);

        Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination = {
            DestinationX, DestinationY};
      }

      auto DeltaX =
          Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination.X -
          Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.X;
      auto DeltaY =
          Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination.Y -
          Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.Y;
      auto Distance = std::sqrt(DeltaX * DeltaX + DeltaY * DeltaY);

      if (Distance < 1) {
        Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination = {-1, -1};

        continue;
      }

      auto PiF = static_cast<float>(M_PI);

      Engine.GetCurrentMapArea().Tiles[X][Y].Mob->FacingAngle =
          static_cast<float>(std::atan2(-DeltaX, -DeltaY)) / PiF * 180.0f;

      auto Angle = Engine.GetCurrentMapArea().Tiles[X][Y].Mob->FacingAngle /
                       180.0f * PiF -
                   PiF / 2 + PiF;
      auto DX = -std::cos(Angle) *
                Engine.GetCurrentMapArea().Tiles[X][Y].Mob->StepMultiplier;
      auto DY = std::sin(Angle) *
                Engine.GetCurrentMapArea().Tiles[X][Y].Mob->StepMultiplier;
      auto NewX =
          float(Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.X +
                DX * Engine.GetCurrentMapArea().Tiles[X][Y].Mob->StepSize);
      auto NewY =
          float(Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.Y +
                DY * Engine.GetCurrentMapArea().Tiles[X][Y].Mob->StepSize);
      auto NewXI = static_cast<int>(NewX);
      auto NewYI = static_cast<int>(NewY);
      auto OldXI = static_cast<int>(Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.X);
      auto OldYI = static_cast<int>(Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.Y);

      if (NewXI >= 0 && NewYI >= 0 && NewXI < Engine.WorldMap->MapAreaSize &&
          NewYI < Engine.WorldMap->MapAreaSize) {
        if (Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].GroundType !=
            GetId("GroundtypeWater")) {
          if (Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Mob == nullptr ||
              (NewXI == OldXI && NewYI == OldYI)) {
            Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Mob->Position = {
                NewX, NewY};

            if (NewXI != OldXI || NewYI != OldYI) {
              Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Mob =
                  std::move(Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Mob);
              Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Mob = nullptr;
            }

            Engine.GetCurrentMapArea().MobsMirror.erase(
                Engine.GetCurrentMapArea().MobsMirror.begin() + I);
            Engine.GetCurrentMapArea().MobsMirror.push_back(
                std::ref(Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Mob));
          } else if (Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Mob !=
                         nullptr &&
                     (NewXI != OldXI || NewYI != OldYI)) {
            Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination = {-1,
                                                                           -1};
          }
        } else {
          Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination = {-1,
                                                                         -1};
        }
      } else {
        Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination = {-1, -1};
      }
    }
  }
}

}  // namespace Forradia
