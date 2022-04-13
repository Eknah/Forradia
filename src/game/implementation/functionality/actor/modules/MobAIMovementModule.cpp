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

        if (actor.actorId == e.GetPlayer().actorId)
            return;

        if (mob.actorId == e.GetPlayer().actorId)
            return;

        mob.GetModule<CoreMovementModule>().isWalking = true;

        if (Ticks() > mob.GetModule<CoreMovementModule>().tickLastMove + mob.GetModule<CoreMovementModule>().moveSpeed)
        {
            mob.GetModule<CoreMovementModule>().tickLastMove = Ticks();

            if (mob.GetModule<CoreMovementModule>().destination.x == -1 || mob.GetModule<CoreMovementModule>().destination.y == -1)
            {

                auto destinationX =
                    mob.GetModule<CoreMovementModule>().position.x + rnd.Next() % 15 - rnd.Next() % 15;
                auto destinationY =
                    mob.GetModule<CoreMovementModule>().position.y + rnd.Next() % 15 - rnd.Next() % 15;

                destinationX =
                    std::min(std::max(destinationX, 0.0f),
                        static_cast<float>(e.world->mapAreaSize) - 1.0f);
                destinationY =
                    std::min(std::max(destinationY, 0.0f),
                        static_cast<float>(e.world->mapAreaSize) - 1.0f);

                GetParentActor().GetModule<CoreMovementModule>().destination = { destinationX, destinationY };
            }

            auto deltaX = mob.GetModule<CoreMovementModule>().destination.x - mob.GetModule<CoreMovementModule>().position.x;
            auto deltaY = mob.GetModule<CoreMovementModule>().destination.y - mob.GetModule<CoreMovementModule>().position.y;
            auto distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

            if (distance < 1)
            {
                mob.GetModule<CoreMovementModule>().destination = { -1, -1 };

                return;
            }

            auto piF = static_cast<float>(M_PI);

            *mob.GetModule<CoreMovementModule>().facingAngle =
                static_cast<float>(std::atan2(-deltaX, -deltaY)) / piF * 180.0f;

            auto angle = *mob.GetModule<CoreMovementModule>().facingAngle / 180.0f * piF - piF / 2 + piF;
            auto dx = -std::cos(angle) * mob.GetModule<CoreMovementModule>().stepMultiplier;
            auto dy = std::sin(angle) * mob.GetModule<CoreMovementModule>().stepMultiplier;
            auto newX = static_cast<float>(mob.GetModule<CoreMovementModule>().position.x + dx * mob.GetModule<CoreMovementModule>().stepSize);
            auto newY = static_cast<float>(mob.GetModule<CoreMovementModule>().position.y + dy * mob.GetModule<CoreMovementModule>().stepSize);
            auto newXI = static_cast<int>(newX);
            auto newYI = static_cast<int>(newY);
            auto oldXI = static_cast<int>(mob.GetModule<CoreMovementModule>().position.x);
            auto oldYI = static_cast<int>(mob.GetModule<CoreMovementModule>().position.y);

            if (newXI >= 0 && newYI >= 0 && newXI < e.world->mapAreaSize &&
                newYI < e.world->mapAreaSize)
            {
                if (e.GetCurrMapArea().tiles[newXI][newYI].groundType !=
                    GetId("GroundTypeWater"))
                {
                    if (e.GetCurrMapArea().tiles[newXI][newYI].actor == nullptr ||
                        (newXI == oldXI && newYI == oldYI))
                    {
                        e.GetCurrMapArea().tiles[oldXI][oldYI].actor->GetModule<CoreMovementModule>().position = {
                            newX, newY };

                        if (newXI != oldXI || newYI != oldYI)
                        {
                            e.GetCurrMapArea().tiles[newXI][newYI].actor = std::move(
                                e.GetCurrMapArea().tiles[oldXI][oldYI].actor);
                            e.GetCurrMapArea().tiles[oldXI][oldYI].actor = nullptr;
                        }

                        e.GetCurrMapArea().mobActorsMirror.erase(mob.actorId);

                        e.GetCurrMapArea().mobActorsMirror.insert({ e.GetCurrMapArea().tiles[newXI][newYI].actor->actorId,
                            std::ref(e.GetCurrMapArea().tiles[newXI][newYI].actor) });

                    }
                    else if (e.GetCurrMapArea().tiles[newXI][newYI].actor !=
                        nullptr &&
                        (newXI != oldXI || newYI != oldYI))
                    {
                        mob.GetModule<CoreMovementModule>().destination = { -1, -1 };
                    }

                }
                else
                {
                    mob.GetModule<CoreMovementModule>().destination = { -1, -1 };
                }

            }
            else
            {
                mob.GetModule<CoreMovementModule>().destination = { -1, -1 };
            }
        }
    }

}  // namespace Forradia
