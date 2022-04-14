// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "DirectionMovmModule.h"
#include "../engine/Aliases.h"
#include "../engine/IEngine.h"
#include "../engine/Actor.h"
#include "CoreMovmModule.h"
#include "WarpMovmModule.h"

namespace Forradia
{

    DirectionMovmModule::DirectionMovmModule(const IEngine& _e, Actor* parentActor_) : IModule(_e, parentActor_)
    {
        GetParentActor().AddIfNotExists<CoreMovmModule>();
        GetParentActor().AddIfNotExists<WarpMovmModule>();
    }

    void DirectionMovmModule::Update()
    {

        auto& actor = GetParentActor();
        auto& coreMovm = actor.GetModule<CoreMovmModule>();

        if (!coreMovm.timer.HasFinished()) return;
        if (!(moveInstruction & DirForward || moveInstruction & DirRight || moveInstruction & DirBack || moveInstruction & DirLeft))
            return;

        coreMovm.isWalking = true;

        auto newX = coreMovm.position.x;
        auto newY = coreMovm.position.y;
        auto angle = 0.0f;
        auto piF = CFloat(M_PI);

        if (moveInstruction & DirForward && moveInstruction & DirLeft)
        {
            angle = *coreMovm.facingAngle / 180.0f * piF - piF / 2.0f + 0.5f * piF / 2.0f;
            *coreMovm.facingAngle = *coreMovm.facingAngle + 0.5 * 90.0f;
        }
        else if (moveInstruction & DirLeft && moveInstruction & DirBack)
        {
            angle = *coreMovm.facingAngle / 180.0f * piF - piF / 2.0f + 1.5f * piF / 2.0f;
            *coreMovm.facingAngle = *coreMovm.facingAngle + 1.5 * 90.0f;
        }
        else if (moveInstruction & DirBack && moveInstruction & DirRight)
        {
            angle = *coreMovm.facingAngle / 180.0f * piF - piF / 2.0f + 2.5f * piF / 2.0f;
            *coreMovm.facingAngle = *coreMovm.facingAngle + 2.5 * 90.0f;
        }
        else if (moveInstruction & DirRight && moveInstruction & DirForward)
        {
            angle = *coreMovm.facingAngle / 180.0f * piF - piF / 2.0f + 3.5f * piF / 2.0f;
            *coreMovm.facingAngle = *coreMovm.facingAngle + 3.5f * 90.0f;
        }
        else if (moveInstruction & DirForward)
        {
            angle = *coreMovm.facingAngle / 180.0f * piF - piF / 2.0f + 0.0f * piF / 2.0f;
        }
        else if (moveInstruction & DirLeft)
        {
            angle = *coreMovm.facingAngle / 180.0f * piF - piF / 2.0f + 1.0f * piF / 2.0f;
            *coreMovm.facingAngle = *coreMovm.facingAngle + 1 * 90.0f;
        }
        else if (moveInstruction & DirBack)
        {
            angle = *coreMovm.facingAngle / 180.0f * piF - piF / 2.0f + 2.0f * piF / 2.0f;
        }
        else if (moveInstruction & DirRight)
        {
            angle = *coreMovm.facingAngle / 180.0f * piF - piF / 2.0f + 3.0f * piF / 2.0f;
            *coreMovm.facingAngle = *coreMovm.facingAngle + 3.0f * 90.0f;
        }

        auto dx = -std::cos(angle) * coreMovm.stepMultiplier;
        auto dy = std::sin(angle) * coreMovm.stepMultiplier;

        newX += dx * coreMovm.stepSize;
        newY += dy * coreMovm.stepSize;

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

        coreMovm.timer.Reset();
    }



}  // namespace Forradia
