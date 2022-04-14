// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "MobAIMovmModule.h"
#include "../engine/IEngine.h"
#include "CoreMovmModule.h"
#include <iostream>

namespace Forradia
{

    MobAIMovmModule::MobAIMovmModule(const IEngine& _e, Actor* parentActor_) : IModule(_e, parentActor_)
    {
        GetParentActor().AddIfNotExists<CoreMovmModule>();
    }

    void MobAIMovmModule::Update()
    {
        auto& actor = GetParentActor();
        auto& mob = actor;
        auto& coreMovm = mob.GetModule<CoreMovmModule>();

        if (actor.actorId == e.GetPlayer().actorId) return;
        if (mob.actorId == e.GetPlayer().actorId) return;

        coreMovm.isWalking = true;

        if (coreMovm.timer.HasFinished())
        {

            if (coreMovm.dest.x == -1 || coreMovm.dest.y == -1)
            {

                auto destx = coreMovm.position.x + rnd.Next() % 15 - rnd.Next() % 15;
                auto desty = coreMovm.position.y + rnd.Next() % 15 - rnd.Next() % 15;

                destx = std::min(std::max(destx, 0.0f), CFloat(e.world->mapAreaSize) - 1.0f);
                desty = std::min(std::max(desty, 0.0f), CFloat(e.world->mapAreaSize) - 1.0f);

                coreMovm.dest = { destx, desty };
            }

            auto deltaX = coreMovm.dest.x - coreMovm.position.x;
            auto deltaY = coreMovm.dest.y - coreMovm.position.y;
            auto distance = deltaX * deltaX + deltaY * deltaY;

            if (distance < 1.0f)
            {
                coreMovm.dest = { -1, -1 };

                return;
            }

            auto piF = CFloat(M_PI);

            *coreMovm.facingAngle = std::atan2(-deltaX, -deltaY) / piF * 180.0f;

            auto angle = *coreMovm.facingAngle / 180.0f * piF - piF / 2 + piF;
            auto dx = -std::cos(angle) * coreMovm.stepMultiplier;
            auto dy = std::sin(angle) * coreMovm.stepMultiplier;
            auto newX = coreMovm.position.x + dx * coreMovm.stepSize;
            auto newY = coreMovm.position.y + dy * coreMovm.stepSize;
            auto newXI = CInt(newX);
            auto newYI = CInt(newY);
            auto oldXI = CInt(coreMovm.position.x);
            auto oldYI = CInt(coreMovm.position.y);

            if (newXI >= 0 && newYI >= 0 && newXI < e.world->mapAreaSize && newYI < e.world->mapAreaSize)
            {
                if (e.GetCurrMapArea().tiles[newXI][newYI].groundType != GetId("GroundTypeWater"))
                {
                    if (e.GetCurrMapArea().tiles[newXI][newYI].actor == nullptr || (newXI == oldXI && newYI == oldYI))
                    {

                        coreMovm.timer.Reset();
                        e.GetCurrMapArea().tiles[oldXI][oldYI].actor->GetModule<CoreMovmModule>().position = {newX, newY };

                        if (newXI != oldXI || newYI != oldYI)
                        {
                            e.GetCurrMapArea().tiles[newXI][newYI].actor = std::move(e.GetCurrMapArea().tiles[oldXI][oldYI].actor);
                            e.GetCurrMapArea().tiles[oldXI][oldYI].actor = nullptr;
                            e.GetCurrMapArea().mobActorsMirror.erase(mob.actorId);
                            e.GetCurrMapArea().mobActorsMirror.insert({ e.GetCurrMapArea().tiles[newXI][newYI].actor->actorId, std::ref(e.GetCurrMapArea().tiles[newXI][newYI].actor) });

                        }

                    }
                    else if (e.GetCurrMapArea().tiles[newXI][newYI].actor != nullptr && (newXI != oldXI || newYI != oldYI))
                    {
                        coreMovm.dest = { -1, -1 };
                    }

                }
                else
                {
                    coreMovm.dest = { -1, -1 };
                }

            }
            else
            {
                coreMovm.dest = { -1, -1 };
            }
        }
    }

}  // namespace Forradia
