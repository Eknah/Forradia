// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "DestMovementModule.h"
#include "../engine/Aliases.h"
#include "../engine/IEngine.h"
#include "../engine/Actor.h"
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
        auto& coreMovm = actor.GetModule<CoreMovementModule>();

        if (!coreMovm.timer.HasFinished()) return;
        if (coreMovm.dest.IsUndefined()) return;

        auto dx = coreMovm.dest.x - coreMovm.position.x;
        auto dy = coreMovm.dest.y - coreMovm.position.y;
        auto absdx = std::abs(dx);
        auto absdy = std::abs(dy);

        if (absdx < coreMovm.stepMultiplier && absdy < coreMovm.stepMultiplier)
        {
            coreMovm.dest.MakeUndefined();
        }
        else
        {
            auto piF = CFloat(M_PI);
            coreMovm.isWalking = true;
            *coreMovm.facingAngle = CFloat(std::atan2(-dx, -dy)) / piF * 180.0f;

            auto angle = *coreMovm.facingAngle / 180.0f * piF - piF / 2 + 0 * piF / 2;
            auto dx = -std::cos(angle) * coreMovm.stepMultiplier;
            auto dy = std::sin(angle) * coreMovm.stepMultiplier;
            auto newX = coreMovm.position.x + dx * coreMovm.stepSize;
            auto newY = coreMovm.position.y + dy * coreMovm.stepSize;

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

            coreMovm.TryMoveToTile(newXRounded, newYRounded);

        }

        coreMovm.timer.Reset();
    }

}  // namespace Forradia
