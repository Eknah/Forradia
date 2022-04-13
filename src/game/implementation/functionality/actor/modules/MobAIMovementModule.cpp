// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "MobAIMovementModule.h"
#include "../engine/IEngine.h"
#include "CoreMovementModule.h"
#include <iostream>

namespace Forradia
{

    MobAIMovementModule::MobAIMovementModule(const IEngine& _e,
        Actor* parentActor_)
        : IModule(_e, parentActor_)
    {
        GetParentActor().AddIfNotExists<CoreMovementModule>();
    }

    void MobAIMovementModule::Update()
    {
        auto& actor = GetParentActor();
        auto& mob = actor;
        auto& coreMovement = mob.GetModule<CoreMovementModule>();

        if (actor.actorId == e.GetPlayer().actorId) return;
        if (mob.actorId == e.GetPlayer().actorId) return;

        coreMovement.isWalking = true;

        if (coreMovement.timer.HasFinished())
        {
            coreMovement.timer.Reset();

            if (coreMovement.destination.x == -1 || coreMovement.destination.y == -1)
            {

                auto destinationX = coreMovement.position.x + rnd.Next() % 15 - rnd.Next() % 15;
                auto destinationY = coreMovement.position.y + rnd.Next() % 15 - rnd.Next() % 15;

                destinationX = std::min(std::max(destinationX, 0.0f), CFloat(e.world->mapAreaSize) - 1.0f);
                destinationY = std::min(std::max(destinationY, 0.0f), CFloat(e.world->mapAreaSize) - 1.0f);

                GetParentActor().GetModule<CoreMovementModule>().destination = { destinationX, destinationY };
            }

            auto deltaX = coreMovement.destination.x - coreMovement.position.x;
            auto deltaY = coreMovement.destination.y - coreMovement.position.y;
            auto distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

            if (distance < 1)
            {
                coreMovement.destination = { -1, -1 };

                return;
            }

            auto piF = CFloat(M_PI);

            *coreMovement.facingAngle = std::atan2(-deltaX, -deltaY) / piF * 180.0f;

            auto angle = *coreMovement.facingAngle / 180.0f * piF - piF / 2 + piF;
            auto dx = -std::cos(angle) * coreMovement.stepMultiplier;
            auto dy = std::sin(angle) * coreMovement.stepMultiplier;
            auto newX = coreMovement.position.x + dx * coreMovement.stepSize;
            auto newY = coreMovement.position.y + dy * coreMovement.stepSize;
            auto newXI = CInt(newX);
            auto newYI = CInt(newY);
            auto oldXI = CInt(coreMovement.position.x);
            auto oldYI = CInt(coreMovement.position.y);

            if (newXI >= 0 && newYI >= 0 && newXI < e.world->mapAreaSize && newYI < e.world->mapAreaSize)
            {
                if (e.GetCurrMapArea().tiles[newXI][newYI].groundType != GetId("GroundTypeWater"))
                {
                    if (e.GetCurrMapArea().tiles[newXI][newYI].actor == nullptr || (newXI == oldXI && newYI == oldYI))
                    {
                        e.GetCurrMapArea().tiles[oldXI][oldYI].actor->GetModule<CoreMovementModule>().position = {newX, newY };

                        if (newXI != oldXI || newYI != oldYI)
                        {
                            e.GetCurrMapArea().tiles[newXI][newYI].actor = std::move(e.GetCurrMapArea().tiles[oldXI][oldYI].actor);
                            e.GetCurrMapArea().tiles[oldXI][oldYI].actor = nullptr;
                        }

                        e.GetCurrMapArea().mobActorsMirror.erase(mob.actorId);

                        e.GetCurrMapArea().mobActorsMirror.insert({ e.GetCurrMapArea().tiles[newXI][newYI].actor->actorId, std::ref(e.GetCurrMapArea().tiles[newXI][newYI].actor) });

                    }
                    else if (e.GetCurrMapArea().tiles[newXI][newYI].actor != nullptr && (newXI != oldXI || newYI != oldYI))
                    {
                        coreMovement.destination = { -1, -1 };
                    }

                }
                else
                {
                    coreMovement.destination = { -1, -1 };
                }

            }
            else
            {
                coreMovement.destination = { -1, -1 };
            }
        }
    }

}  // namespace Forradia
