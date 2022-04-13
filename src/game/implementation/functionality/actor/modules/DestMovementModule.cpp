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
        GetParentActor().AddIfNotExists<MovementDataModule>();
        GetParentActor().AddIfNotExists<WarpMovementModule>();
    }

    void DestMovementModule::Update()
    {
        auto& actor = GetParentActor();
        auto& movementData = actor.GetModule<MovementDataModule>();

        if (Ticks() < movementData.tickLastMove + movementData.moveSpeed) return;
        if (movementData.moveDestination.IsUndefined()) return;

        auto dx = movementData.moveDestination.x - movementData.position.x;
        auto dy = movementData.moveDestination.y - movementData.position.y;
        auto absDx = std::abs(dx);
        auto absDy = std::abs(dy);
        auto piF = static_cast<float>(M_PI);

        if (absDx < movementData.stepMultiplier && absDy < movementData.stepMultiplier)
        {
            movementData.moveDestination = { -1, -1 };
        }
        else
        {
            movementData.isWalking = true;
            *movementData.facingAngle
                = static_cast<float>(std::atan2(-dx, -dy)) / piF * 180.0f;

            auto angle = *movementData.facingAngle / 180.0f * piF - piF / 2 +
                0 * piF / 2;
            auto dx = -static_cast<float>(std::cos(angle)) * movementData.stepMultiplier;
            auto dy = static_cast<float>(std::sin(angle)) * movementData.stepMultiplier;
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
            auto newXRoundedI = static_cast<int>(newXRounded);
            auto newYRoundedI = static_cast<int>(newYRounded);

            auto tileHasMob = false;

            if (e.GetCurrentMapArea()
                .tiles[newXRoundedI][newYRoundedI].actor != nullptr)
            {
                if (e.GetCurrentMapArea()
                    .tiles[newXRoundedI][newYRoundedI].actor->actorId != e.GetPlayer().actorId)
                    tileHasMob = true;
            }

            if (!e.GetCurrentMapArea()
                .tiles[newXRoundedI][newYRoundedI]
                .HasObjectWithFlag(FlagObstacle)
                && e.GetCurrentMapArea()
                .tiles[newXRoundedI][newYRoundedI].groundType != GetId("GroundTypeWater")
                && !tileHasMob)
            {
                auto oldXI = static_cast<int>(movementData.position.x);
                auto oldYI = static_cast<int>(movementData.position.y);

                movementData.position.x = newXRounded;
                movementData.position.y = newYRounded;

                if (newXRoundedI != oldXI || newYRoundedI != oldYI)
                {
                    e.GetCurrentMapArea().tiles[newXRoundedI][newYRoundedI].actor
                        = std::move(e.GetCurrentMapArea().tiles[oldXI][oldYI].actor);
                    e.GetCurrentMapArea().tiles[oldXI][oldYI].actor = nullptr;
                }
            }

            actor.GetModule<WarpMovementModule>().WarpIfStandOnPortal();
        }

        movementData.tickLastMove = Ticks();
    }

}  // namespace Forradia
