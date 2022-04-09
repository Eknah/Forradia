// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <algorithm>
#include <utility>
#include "MobsEngine.h"
#include "../engine/Engine.h"
#include "implementation/functionality/actor/modules/MovementDataModule.h"

namespace Forradia {

void MobsEngine::Update() {
  for (unsigned int i = 0;
       i < e.GetCurrentMapArea().mobActorsMirror.size(); i++) {
    if (i >= e.GetCurrentMapArea().mobActorsMirror.size())
      break;

    SPtr<Mob> mobPtr = std::dynamic_pointer_cast<Mob>(
        e.GetCurrentMapArea().mobActorsMirror.at(i).get());

    if (mobPtr == nullptr)
      continue;

    Actor &actor =
        *e.GetCurrentMapArea().mobActorsMirror.at(i).get().get();

    if (actor.actorId == e.GetPlayer().actorId)
      continue;

    Mob &mob = *mobPtr;

    if (mob.actorId == e.GetPlayer().actorId)
      continue;

    if (Ticks() > mob.GetModule<MovementDataModule>().tickLastMove + mob.GetModule<MovementDataModule>().moveSpeed) {
      mob.GetModule<MovementDataModule>().tickLastMove = Ticks();

      if (mob.GetModule<MovementDataModule>().moveDestination.x == -1 || mob.GetModule<MovementDataModule>().moveDestination.y == -1) {
        auto destinationX =
            mob.GetModule<MovementDataModule>().position.x + random.Next() % 15 - random.Next() % 15;
        auto destinationY =
            mob.GetModule<MovementDataModule>().position.y + random.Next() % 15 - random.Next() % 15;

        destinationX =
            std::min(std::max(destinationX, 0.0f),
                     static_cast<float>(e.world->mapAreaSize) - 1.0f);
        destinationY =
            std::min(std::max(destinationY, 0.0f),
                     static_cast<float>(e.world->mapAreaSize) - 1.0f);

        mob.GetModule<MovementDataModule>().moveDestination = {destinationX, destinationY};
      }

      auto deltaX = mob.GetModule<MovementDataModule>().moveDestination.x - mob.GetModule<MovementDataModule>().position.x;
      auto deltaY = mob.GetModule<MovementDataModule>().moveDestination.y - mob.GetModule<MovementDataModule>().position.y;
      auto distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

      if (distance < 1) {
        mob.GetModule<MovementDataModule>().moveDestination = {-1, -1};

        continue;
      }

      auto piF = static_cast<float>(M_PI);

      *mob.GetModule<MovementDataModule>().facingAngle =
          static_cast<float>(std::atan2(-deltaX, -deltaY)) / piF * 180.0f;

      auto angle = *mob.GetModule<MovementDataModule>().facingAngle / 180.0f * piF - piF / 2 + piF;
      auto dx = -std::cos(angle) * mob.GetModule<MovementDataModule>().stepMultiplier;
      auto dy = std::sin(angle) * mob.GetModule<MovementDataModule>().stepMultiplier;
      auto newX = static_cast<float>(mob.GetModule<MovementDataModule>().position.x + dx * mob.GetModule<MovementDataModule>().stepSize);
      auto newY = static_cast<float>(mob.GetModule<MovementDataModule>().position.y + dy * mob.GetModule<MovementDataModule>().stepSize);
      auto newXI = static_cast<int>(newX);
      auto newYI = static_cast<int>(newY);
      auto oldXI = static_cast<int>(mob.GetModule<MovementDataModule>().position.x);
      auto oldYI = static_cast<int>(mob.GetModule<MovementDataModule>().position.y);

      if (newXI >= 0 && newYI >= 0 && newXI < e.world->mapAreaSize &&
          newYI < e.world->mapAreaSize) {
        if (e.GetCurrentMapArea().tiles[newXI][newYI].groundType !=
            GetId("GroundTypeWater")) {
          if (e.GetCurrentMapArea().tiles[newXI][newYI].actor == nullptr ||
              (newXI == oldXI && newYI == oldYI)) {
            e.GetCurrentMapArea().tiles[oldXI][oldYI].actor->GetModule<MovementDataModule>().position = {
                newX, newY};

            if (newXI != oldXI || newYI != oldYI) {
              e.GetCurrentMapArea().tiles[newXI][newYI].actor = std::move(
                  e.GetCurrentMapArea().tiles[oldXI][oldYI].actor);
              e.GetCurrentMapArea().tiles[oldXI][oldYI].actor = nullptr;
            }

            e.GetCurrentMapArea().mobActorsMirror.erase(
                e.GetCurrentMapArea().mobActorsMirror.begin() + i);
            e.GetCurrentMapArea().mobActorsMirror.push_back(
                std::ref(e.GetCurrentMapArea().tiles[newXI][newYI].actor));

          } else if (e.GetCurrentMapArea().tiles[newXI][newYI].actor !=
                         nullptr &&
                     (newXI != oldXI || newYI != oldYI)) {
            mob.GetModule<MovementDataModule>().moveDestination = {-1, -1};
          }

        } else {
          mob.GetModule<MovementDataModule>().moveDestination = {-1, -1};
        }

      } else {
        mob.GetModule<MovementDataModule>().moveDestination = {-1, -1};
      }
    }
  }
}

}  // namespace Forradia
