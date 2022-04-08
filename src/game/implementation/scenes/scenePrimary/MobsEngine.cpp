// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <algorithm>
#include <utility>
#include "MobsEngine.h"
#include "../engine/Engine.h"
#include "implementation/functionality/actor/modules/ModuleMovementData.h"

namespace Forradia {

void cMobsEngine::Update() {
  for (unsigned int i = 0;
       i < engine.GetCurrentMapArea().mobActorsMirror.size(); i++) {
    if (i >= engine.GetCurrentMapArea().mobActorsMirror.size())
      break;

    SPtr<cMob> mobPtr = std::dynamic_pointer_cast<cMob>(
        engine.GetCurrentMapArea().mobActorsMirror.at(i).get());

    if (mobPtr == nullptr)
      continue;

    cActor &actor =
        *engine.GetCurrentMapArea().mobActorsMirror.at(i).get().get();

    if (actor.actorId == engine.GetPlayer().actorId)
      continue;

    cMob &mob = *mobPtr;

    if (mob.actorId == engine.GetPlayer().actorId)
      continue;

    if (Ticks() > mob.GetModule<cModuleMovementData>().tickLastMove + mob.GetModule<cModuleMovementData>().moveSpeed) {
      mob.GetModule<cModuleMovementData>().tickLastMove = Ticks();

      if (mob.GetModule<cModuleMovementData>().moveDestination.x == -1 || mob.GetModule<cModuleMovementData>().moveDestination.y == -1) {
        auto destinationX =
            mob.GetModule<cModuleMovementData>().position.x + random.Next() % 15 - random.Next() % 15;
        auto destinationY =
            mob.GetModule<cModuleMovementData>().position.y + random.Next() % 15 - random.Next() % 15;

        destinationX =
            std::min(std::max(destinationX, 0.0f),
                     static_cast<float>(engine.world->mapAreaSize) - 1.0f);
        destinationY =
            std::min(std::max(destinationY, 0.0f),
                     static_cast<float>(engine.world->mapAreaSize) - 1.0f);

        mob.GetModule<cModuleMovementData>().moveDestination = {destinationX, destinationY};
      }

      auto deltaX = mob.GetModule<cModuleMovementData>().moveDestination.x - mob.GetModule<cModuleMovementData>().position.x;
      auto deltaY = mob.GetModule<cModuleMovementData>().moveDestination.y - mob.GetModule<cModuleMovementData>().position.y;
      auto distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

      if (distance < 1) {
        mob.GetModule<cModuleMovementData>().moveDestination = {-1, -1};

        continue;
      }

      auto piF = static_cast<float>(M_PI);

      *mob.GetModule<cModuleMovementData>().facingAngle =
          static_cast<float>(std::atan2(-deltaX, -deltaY)) / piF * 180.0f;

      auto angle = *mob.GetModule<cModuleMovementData>().facingAngle / 180.0f * piF - piF / 2 + piF;
      auto dx = -std::cos(angle) * mob.GetModule<cModuleMovementData>().stepMultiplier;
      auto dy = std::sin(angle) * mob.GetModule<cModuleMovementData>().stepMultiplier;
      auto newX = static_cast<float>(mob.GetModule<cModuleMovementData>().position.x + dx * mob.GetModule<cModuleMovementData>().stepSize);
      auto newY = static_cast<float>(mob.GetModule<cModuleMovementData>().position.y + dy * mob.GetModule<cModuleMovementData>().stepSize);
      auto newXI = static_cast<int>(newX);
      auto newYI = static_cast<int>(newY);
      auto oldXI = static_cast<int>(mob.GetModule<cModuleMovementData>().position.x);
      auto oldYI = static_cast<int>(mob.GetModule<cModuleMovementData>().position.y);

      if (newXI >= 0 && newYI >= 0 && newXI < engine.world->mapAreaSize &&
          newYI < engine.world->mapAreaSize) {
        if (engine.GetCurrentMapArea().tiles[newXI][newYI].groundType !=
            GetId("GroundTypeWater")) {
          if (engine.GetCurrentMapArea().tiles[newXI][newYI].actor == nullptr ||
              (newXI == oldXI && newYI == oldYI)) {
            engine.GetCurrentMapArea().tiles[oldXI][oldYI].actor->GetModule<cModuleMovementData>().position = {
                newX, newY};

            if (newXI != oldXI || newYI != oldYI) {
              engine.GetCurrentMapArea().tiles[newXI][newYI].actor = std::move(
                  engine.GetCurrentMapArea().tiles[oldXI][oldYI].actor);
              engine.GetCurrentMapArea().tiles[oldXI][oldYI].actor = nullptr;
            }

            engine.GetCurrentMapArea().mobActorsMirror.erase(
                engine.GetCurrentMapArea().mobActorsMirror.begin() + i);
            engine.GetCurrentMapArea().mobActorsMirror.push_back(
                std::ref(engine.GetCurrentMapArea().tiles[newXI][newYI].actor));

          } else if (engine.GetCurrentMapArea().tiles[newXI][newYI].actor !=
                         nullptr &&
                     (newXI != oldXI || newYI != oldYI)) {
            mob.GetModule<cModuleMovementData>().moveDestination = {-1, -1};
          }

        } else {
          mob.GetModule<cModuleMovementData>().moveDestination = {-1, -1};
        }

      } else {
        mob.GetModule<cModuleMovementData>().moveDestination = {-1, -1};
      }
    }
  }
}

}  // namespace Forradia
