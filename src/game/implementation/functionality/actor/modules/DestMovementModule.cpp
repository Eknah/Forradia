// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "DestMovementModule.h"
#include "../engine/Aliases.h"
#include "../engine/IEngine.h"
#include "implementation/functionality/actor/Actor.h"
#include "CoreMovementModule.h"
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
        auto& coreMovement = actor.GetModule<CoreMovementModule>();

        if (Ticks() < coreMovement.tickLastMove + coreMovement.moveSpeed) return;
        if (coreMovement.destination.IsUndefined()) return;

        auto dx = coreMovement.destination.x - coreMovement.position.x;
        auto dy = coreMovement.destination.y - coreMovement.position.y;
        auto absdx = std::abs(dx);
        auto absdy = std::abs(dy);

        if (absdx < coreMovement.stepMultiplier && absdy < coreMovement.stepMultiplier)
        {
            coreMovement.destination.MakeUndefined();
        }
        else
        {
            auto piF = CFloat(M_PI);
            coreMovement.isWalking = true;
            *coreMovement.facingAngle = CFloat(std::atan2(-dx, -dy)) / piF * 180.0f;

            auto angle = *coreMovement.facingAngle / 180.0f * piF - piF / 2 + 0 * piF / 2;
            auto dx = -std::cos(angle) * coreMovement.stepMultiplier;
            auto dy = std::sin(angle) * coreMovement.stepMultiplier;
            auto newX = coreMovement.position.x + dx * coreMovement.stepSize;
            auto newY = coreMovement.position.y + dy * coreMovement.stepSize;

            if (newX < 0)
                newX += e.GetCurrMapArea().size;
            if (newY < 0)
                newY += e.GetCurrMapArea().size;
            if (newX >= e.GetCurrMapArea().size)
                newX -= e.GetCurrMapArea().size;
            if (newY >= e.GetCurrMapArea().size)
                newY -= e.GetCurrMapArea().size;

            auto newXRounded = newX;
            auto newYRounded = newY;

            coreMovement.TryMoveToTile(newXRounded, newYRounded);

        }

        coreMovement.tickLastMove = Ticks();
    }

}  // namespace Forradia
