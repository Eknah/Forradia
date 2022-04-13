// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "DirectionMovementModule.h"
#include "../engine/Aliases.h"
#include "../engine/IEngine.h"
#include "implementation/functionality/actor/Actor.h"
#include "MovementDataModule.h"
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
        auto& movementData = actor.GetModule<CoreMovementModule>();

        if (Ticks() < movementData.tickLastMove + movementData.moveSpeed) return;
        if (!(moveInstruction & DirForward || moveInstruction & DirRight || moveInstruction & DirBack || moveInstruction & DirLeft))
            return;

        movementData.isWalking = true;

        auto newX = movementData.position.x;
        auto newY = movementData.position.y;
        auto angle = 0.0f;
        auto piF = CFloat(M_PI);

        if (moveInstruction & DirForward && moveInstruction & DirLeft)
        {
            angle = *movementData.facingAngle / 180.0f * piF - piF / 2.0f + 0.5f * piF / 2.0f;
            *movementData.facingAngle = *movementData.facingAngle + 0.5 * 90.0f;
        }
        else if (moveInstruction & DirLeft && moveInstruction & DirBack)
        {
            angle = *movementData.facingAngle / 180.0f * piF - piF / 2.0f + 1.5f * piF / 2.0f;
            *movementData.facingAngle = *movementData.facingAngle + 1.5 * 90.0f;
        }
        else if (moveInstruction & DirBack && moveInstruction & DirRight)
        {
            angle = *movementData.facingAngle / 180.0f * piF - piF / 2.0f + 2.5f * piF / 2.0f;
            *movementData.facingAngle = *movementData.facingAngle + 2.5 * 90.0f;
        }
        else if (moveInstruction & DirRight && moveInstruction & DirForward)
        {
            angle = *movementData.facingAngle / 180.0f * piF - piF / 2.0f + 3.5f * piF / 2.0f;
            *movementData.facingAngle = *movementData.facingAngle + 3.5f * 90.0f;
        }
        else if (moveInstruction & DirForward)
        {
            angle = *movementData.facingAngle / 180.0f * piF - piF / 2.0f + 0.0f * piF / 2.0f;
        }
        else if (moveInstruction & DirLeft)
        {
            angle = *movementData.facingAngle / 180.0f * piF - piF / 2.0f + 1.0f * piF / 2.0f;
            *movementData.facingAngle = *movementData.facingAngle + 1 * 90.0f;
        }
        else if (moveInstruction & DirBack)
        {
            angle = *movementData.facingAngle / 180.0f * piF - piF / 2.0f + 2.0f * piF / 2.0f;
        }
        else if (moveInstruction & DirRight)
        {
            angle = *movementData.facingAngle / 180.0f * piF - piF / 2.0f + 3.0f * piF / 2.0f;
            *movementData.facingAngle = *movementData.facingAngle + 3.0f * 90.0f;
        }

        auto dx = -std::cos(angle) * movementData.stepMultiplier;
        auto dy = std::sin(angle) * movementData.stepMultiplier;

        newX += dx * movementData.stepSize;
        newY += dy * movementData.stepSize;

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

        GetParentActor().GetModule<WarpMovementModule>().WarpIfStandOnPortal();
        movementData.tickLastMove = Ticks();
    }



}  // namespace Forradia
