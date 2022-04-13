// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "DestMovementModule.h"
#include "../engine/Aliases.h"
#include "../engine/IEngine.h"
#include "implementation/functionality/actor/Actor.h"
#include "MovementDataModule.h"
#include "WarpMovementModule.h"

namespace Forradia
{

    DestMovementModule::DestMovementModule(const IEngine& _e, Actor* parentActor_) : IModule(_e, parentActor_)
    {
        GetParentActor().AddIfNotExists<CoreMovementModule>();
        GetParentActor().AddIfNotExists<WarpMovementModule>();
    }

    void DestMovementModule::Update()
    {
        auto& actor = GetParentActor();
        auto& movementData = actor.GetModule<CoreMovementModule>();

        if (Ticks() < movementData.tickLastMove + movementData.moveSpeed) return;
        if (movementData.destination.IsUndefined()) return;

        auto dx = movementData.destination.x - movementData.position.x;
        auto dy = movementData.destination.y - movementData.position.y;
        auto absdx = std::abs(dx);
        auto absdy = std::abs(dy);

        if (absdx < movementData.stepMultiplier && absdy < movementData.stepMultiplier)
        {
            movementData.destination.MakeUndefined();
        }
        else
        {
            auto piF = CFloat(M_PI);
            movementData.isWalking = true;
            *movementData.facingAngle = CFloat(std::atan2(-dx, -dy)) / piF * 180.0f;

            auto angle = *movementData.facingAngle / 180.0f * piF - piF / 2 + 0 * piF / 2;
            auto dx = -std::cos(angle) * movementData.stepMultiplier;
            auto dy = std::sin(angle) * movementData.stepMultiplier;
            auto newX = movementData.position.x + dx * movementData.stepSize;
            auto newY = movementData.position.y + dy * movementData.stepSize;

            if (newX < 0)
                newX += e.GetCurrentMapArea().size;
            if (newY < 0)
                newY += e.GetCurrentMapArea().size;
            if (newX >= e.GetCurrentMapArea().size)
                newX -= e.GetCurrentMapArea().size;
            if (newY >= e.GetCurrentMapArea().size)
                newY -= e.GetCurrentMapArea().size;

            auto newXRounded = newX;
            auto newYRounded = newY;
            auto newXRoundedI = CInt(newXRounded);
            auto newYRoundedI = CInt(newYRounded);

            auto tileHasMob = false;

            if (e.GetCurrentMapArea().tiles[newXRoundedI][newYRoundedI].actor != nullptr)
            {
                if (e.GetCurrentMapArea().tiles[newXRoundedI][newYRoundedI].actor->actorId != e.GetPlayer().actorId)
                    tileHasMob = true;
            }

            if (!e.GetCurrentMapArea().tiles[newXRoundedI][newYRoundedI].HasObjectWithFlag(FlagObstacle)
                && e.GetCurrentMapArea().tiles[newXRoundedI][newYRoundedI].groundType != GetId("GroundTypeWater")
                && !tileHasMob)
            {
                auto oldXI = CInt(movementData.position.x);
                auto oldYI = CInt(movementData.position.y);

                movementData.position.x = newXRounded;
                movementData.position.y = newYRounded;

                if (newXRoundedI != oldXI || newYRoundedI != oldYI)
                {
                    e.GetCurrentMapArea().tiles[newXRoundedI][newYRoundedI].actor = std::move(e.GetCurrentMapArea().tiles[oldXI][oldYI].actor);
                    e.GetCurrentMapArea().tiles[oldXI][oldYI].actor = nullptr;
                }
            }

            actor.GetModule<WarpMovementModule>().WarpIfStandOnPortal();
        }

        movementData.tickLastMove = Ticks();
    }

}  // namespace Forradia
