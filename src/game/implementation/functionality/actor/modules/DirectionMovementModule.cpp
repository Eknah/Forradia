// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "DirectionMovementModule.h"
#include "../engine/Aliases.h"
#include "../engine/IEngine.h"
#include "implementation/functionality/actor/Actor.h"
#include "CoreMovementModule.h"
#include "WarpMovementModule.h"

namespace Forradia
{

    DirectionMovementModule::DirectionMovementModule(const IEngine& _e, Actor* parentActor_) : IModule(_e, parentActor_)
    {
        GetParentActor().AddIfNotExists<CoreMovementModule>();
        GetParentActor().AddIfNotExists<WarpMovementModule>();
    }

    void DirectionMovementModule::Update()
    {

        auto& actor = GetParentActor();
        auto& coreMovement = actor.GetModule<CoreMovementModule>();

        if (!coreMovement.timer.HasFinished()) return;
        if (!(moveInstruction & DirForward || moveInstruction & DirRight || moveInstruction & DirBack || moveInstruction & DirLeft))
            return;

        coreMovement.isWalking = true;

        auto newX = coreMovement.position.x;
        auto newY = coreMovement.position.y;
        auto angle = 0.0f;
        auto piF = CFloat(M_PI);

        if (moveInstruction & DirForward && moveInstruction & DirLeft)
        {
            angle = *coreMovement.facingAngle / 180.0f * piF - piF / 2.0f + 0.5f * piF / 2.0f;
            *coreMovement.facingAngle = *coreMovement.facingAngle + 0.5 * 90.0f;
        }
        else if (moveInstruction & DirLeft && moveInstruction & DirBack)
        {
            angle = *coreMovement.facingAngle / 180.0f * piF - piF / 2.0f + 1.5f * piF / 2.0f;
            *coreMovement.facingAngle = *coreMovement.facingAngle + 1.5 * 90.0f;
        }
        else if (moveInstruction & DirBack && moveInstruction & DirRight)
        {
            angle = *coreMovement.facingAngle / 180.0f * piF - piF / 2.0f + 2.5f * piF / 2.0f;
            *coreMovement.facingAngle = *coreMovement.facingAngle + 2.5 * 90.0f;
        }
        else if (moveInstruction & DirRight && moveInstruction & DirForward)
        {
            angle = *coreMovement.facingAngle / 180.0f * piF - piF / 2.0f + 3.5f * piF / 2.0f;
            *coreMovement.facingAngle = *coreMovement.facingAngle + 3.5f * 90.0f;
        }
        else if (moveInstruction & DirForward)
        {
            angle = *coreMovement.facingAngle / 180.0f * piF - piF / 2.0f + 0.0f * piF / 2.0f;
        }
        else if (moveInstruction & DirLeft)
        {
            angle = *coreMovement.facingAngle / 180.0f * piF - piF / 2.0f + 1.0f * piF / 2.0f;
            *coreMovement.facingAngle = *coreMovement.facingAngle + 1 * 90.0f;
        }
        else if (moveInstruction & DirBack)
        {
            angle = *coreMovement.facingAngle / 180.0f * piF - piF / 2.0f + 2.0f * piF / 2.0f;
        }
        else if (moveInstruction & DirRight)
        {
            angle = *coreMovement.facingAngle / 180.0f * piF - piF / 2.0f + 3.0f * piF / 2.0f;
            *coreMovement.facingAngle = *coreMovement.facingAngle + 3.0f * 90.0f;
        }

        auto dx = -std::cos(angle) * coreMovement.stepMultiplier;
        auto dy = std::sin(angle) * coreMovement.stepMultiplier;

        newX += dx * coreMovement.stepSize;
        newY += dy * coreMovement.stepSize;

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

        coreMovement.timer.Reset();
    }



}  // namespace Forradia
