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

    DirectionMovementModule::DirectionMovementModule(const IEngine& _e,
        Actor* parentActor_)
        : IModule(_e, parentActor_)
    {
        GetParentActor().AddIfNotExists<MovementDataModule>();
        GetParentActor().AddIfNotExists<WarpMovementModule>();
    }

    void DirectionMovementModule::Update()
    {
        if (!(Ticks() > GetParentActor().GetModule<MovementDataModule>().tickLastMove + GetParentActor().GetModule<MovementDataModule>().moveSpeed &&
            (moveInstruction & DirForward || moveInstruction & DirRight ||
                moveInstruction & DirBack || moveInstruction & DirLeft)))
            return;

        GetParentActor().GetModule<MovementDataModule>().isWalking = true;

        auto newX = GetParentActor().GetModule<MovementDataModule>().position.x;
        auto newY = GetParentActor().GetModule<MovementDataModule>().position.y;
        auto angle = 0.0f;
        auto piF = static_cast<float>(M_PI);

        if (moveInstruction & DirForward && moveInstruction & DirLeft)
        {
            angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle /
                180.0f * piF -
                piF / 2.0f + 0.5f * piF / 2.0f;
            *GetParentActor().GetModule<MovementDataModule>().facingAngle =
                *GetParentActor().GetModule<MovementDataModule>().facingAngle +
                0.5 * 90.0f;
        }
        else if (moveInstruction & DirLeft && moveInstruction & DirBack)
        {
            angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle /
                180.0f * piF -
                piF / 2.0f + 1.5f * piF / 2.0f;
            *GetParentActor().GetModule<MovementDataModule>().facingAngle =
                *GetParentActor().GetModule<MovementDataModule>().facingAngle +
                1.5 * 90.0f;
        }
        else if (moveInstruction & DirBack && moveInstruction & DirRight)
        {
            angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle /
                180.0f * piF -
                piF / 2.0f + 2.5f * piF / 2.0f;
            *GetParentActor().GetModule<MovementDataModule>().facingAngle =
                *GetParentActor().GetModule<MovementDataModule>().facingAngle +
                2.5 * 90.0f;
        }
        else if (moveInstruction & DirRight && moveInstruction & DirForward)
        {
            angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle /
                180.0f * piF -
                piF / 2.0f + 3.5f * piF / 2.0f;
            *GetParentActor().GetModule<MovementDataModule>().facingAngle =
                *GetParentActor().GetModule<MovementDataModule>().facingAngle +
                3.5f * 90.0f;
        }
        else if (moveInstruction & DirForward)
        {
            angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle /
                180.0f * piF -
                piF / 2.0f + 0.0f * piF / 2.0f;
        }
        else if (moveInstruction & DirLeft)
        {
            angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle /
                180.0f * piF -
                piF / 2.0f + 1.0f * piF / 2.0f;
            *GetParentActor().GetModule<MovementDataModule>().facingAngle =
                *GetParentActor().GetModule<MovementDataModule>().facingAngle +
                1 * 90.0f;
        }
        else if (moveInstruction & DirBack)
        {
            angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle /
                180.0f * piF -
                piF / 2.0f + 2.0f * piF / 2.0f;
        }
        else if (moveInstruction & DirRight)
        {
            angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle /
                180.0f * piF -
                piF / 2.0f + 3.0f * piF / 2.0f;
            *GetParentActor().GetModule<MovementDataModule>().facingAngle =
                *GetParentActor().GetModule<MovementDataModule>().facingAngle +
                3.0f * 90.0f;
        }

        auto dx = -std::cos(angle) * GetParentActor().GetModule<MovementDataModule>().stepMultiplier;
        auto dy = std::sin(angle) * GetParentActor().GetModule<MovementDataModule>().stepMultiplier;

        newX += dx * GetParentActor().GetModule<MovementDataModule>().stepSize;
        newY += dy * GetParentActor().GetModule<MovementDataModule>().stepSize;

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
            .HasObjectWithFlag(ObjObstacle)
            && e.GetCurrentMapArea()
            .tiles[newXRoundedI][newYRoundedI].groundType != GetId("GroundTypeWater")
            && !tileHasMob)
        {
            auto oldXI = static_cast<int>(GetParentActor().GetModule<MovementDataModule>().position.x);
            auto oldYI = static_cast<int>(GetParentActor().GetModule<MovementDataModule>().position.y);

            GetParentActor().GetModule<MovementDataModule>().position.x = newXRounded;
            GetParentActor().GetModule<MovementDataModule>().position.y = newYRounded;

            if (newXRoundedI != oldXI || newYRoundedI != oldYI)
            {
                e.GetCurrentMapArea().tiles[newXRoundedI][newYRoundedI].actor
                    = std::move(e.GetCurrentMapArea().tiles[oldXI][oldYI].actor);
                e.GetCurrentMapArea().tiles[oldXI][oldYI].actor = nullptr;
            }
        }

        GetParentActor().GetModule<WarpMovementModule>().WarpIfStandOnPortal();

        GetParentActor().GetModule<MovementDataModule>().tickLastMove = Ticks();
    }



}  // namespace Forradia
