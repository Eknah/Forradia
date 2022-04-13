// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "MovementDataModule.h"
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

        auto tileHasMob = false;

        if (e.GetCurrentMapArea().tiles[newxRoundedI][newyRoundedI].actor != nullptr)
        {
            if (e.GetCurrentMapArea().tiles[newxRoundedI][newyRoundedI].actor->actorId != e.GetPlayer().actorId)
                tileHasMob = true;
        }

        if (!e.GetCurrentMapArea().tiles[newxRoundedI][newyRoundedI].HasObjectWithFlag(FlagObstacle)
            && e.GetCurrentMapArea().tiles[newxRoundedI][newyRoundedI].groundType != GetId("GroundTypeWater")
            && !tileHasMob)
        {
            auto oldXI = CInt(position.x);
            auto oldYI = CInt(position.y);

            position.x = newxRounded;
            position.y = newyRounded;

            if (newxRoundedI != oldXI || newyRoundedI != oldYI)
            {
                e.GetCurrentMapArea().tiles[newxRoundedI][newyRoundedI].actor = std::move(e.GetCurrentMapArea().tiles[oldXI][oldYI].actor);
                e.GetCurrentMapArea().tiles[oldXI][oldYI].actor = nullptr;
            }
        }

        actor.GetModule<WarpMovementModule>().WarpIfStandOnPortal();
    }

}  // namespace Forradia
