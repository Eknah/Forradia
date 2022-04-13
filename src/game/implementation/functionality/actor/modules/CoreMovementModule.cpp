// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "CoreMovementModule.h"
#include "implementation/functionality/actor/Actor.h"
#include "../engine/IEngine.h"
#include "implementation/functionality/actor/modules/WarpMovementModule.h"

namespace Forradia
{

    void CoreMovementModule::ResetForNewFrame()
    {
        isWalking = false;
    }

    void CoreMovementModule::TryMoveToTile(float newxRounded, float newyRounded)
    {
        auto& actor = GetParentActor();
        auto& e = actor.e;

        auto newxRoundedI = CInt(newxRounded);
        auto newyRoundedI = CInt(newyRounded);

        if (e.GetCurrMapArea().tiles[newxRoundedI][newyRoundedI].actor != nullptr)
            if (e.GetCurrMapArea().tiles[newxRoundedI][newyRoundedI].actor->actorId != e.GetPlayer().actorId)
                return;

        if (!e.GetCurrMapArea().tiles[newxRoundedI][newyRoundedI].HasObjectWithFlag(FlagObstacle)
            && e.GetCurrMapArea().tiles[newxRoundedI][newyRoundedI].groundType != GetId("GroundTypeWater"))
        {
            auto oldxI = CInt(position.x);
            auto oldyI = CInt(position.y);

            position.x = newxRounded;
            position.y = newyRounded;

            if (newxRoundedI != oldxI || newyRoundedI != oldyI)
            {
                e.GetCurrMapArea().tiles[newxRoundedI][newyRoundedI].actor = std::move(e.GetCurrMapArea().tiles[oldxI][oldyI].actor);
                e.GetCurrMapArea().tiles[oldxI][oldyI].actor = nullptr;
            }
        }

        actor.GetModule<WarpMovementModule>().WarpIfStandOnPortal();
    }

}  // namespace Forradia
