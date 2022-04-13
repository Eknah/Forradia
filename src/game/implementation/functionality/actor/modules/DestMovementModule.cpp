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

    DestMovementModule::DestMovementModule(const IEngine& _e,
        Actor* parentActor_)
        : IModule(_e, parentActor_)
    {
        GetParentActor().AddIfNotExists<MovementDataModule>();
        GetParentActor().AddIfNotExists<WarpMovementModule>();
    }

    void DestMovementModule::Update()
    {
        if (!(Ticks() > GetParentActor().GetModule<MovementDataModule>().tickLastMove + GetParentActor().GetModule<MovementDataModule>().moveSpeed && GetParentActor().GetModule<MovementDataModule>().moveDestination.x != -1 &&
            GetParentActor().GetModule<MovementDataModule>().moveDestination.y != -1))
            return;

        auto dx = GetParentActor().GetModule<MovementDataModule>().moveDestination.x - GetParentActor().GetModule<MovementDataModule>().position.x;
        auto dy = GetParentActor().GetModule<MovementDataModule>().moveDestination.y - GetParentActor().GetModule<MovementDataModule>().position.y;
        auto absDx = std::abs(dx);
        auto absDy = std::abs(dy);
        auto piF = static_cast<float>(M_PI);

        if (absDx < GetParentActor().GetModule<MovementDataModule>().stepMultiplier && absDy < GetParentActor().GetModule<MovementDataModule>().stepMultiplier)
        {
            GetParentActor().GetModule<MovementDataModule>().moveDestination = { -1, -1 };
        }
        else
        {
            GetParentActor().GetModule<MovementDataModule>().isWalking = true;
            *GetParentActor().GetModule<MovementDataModule>().facingAngle
                = static_cast<float>(std::atan2(-dx, -dy)) / piF * 180.0f;

            auto angle = *GetParentActor().GetModule<MovementDataModule>().facingAngle / 180.0f * piF - piF / 2 +
                0 * piF / 2;
            auto dx = -static_cast<float>(std::cos(angle)) * GetParentActor().GetModule<MovementDataModule>().stepMultiplier;
            auto dy = static_cast<float>(std::sin(angle)) * GetParentActor().GetModule<MovementDataModule>().stepMultiplier;
            auto newX = GetParentActor().GetModule<MovementDataModule>().position.x + dx * GetParentActor().GetModule<MovementDataModule>().stepSize;
            auto newY = GetParentActor().GetModule<MovementDataModule>().position.y + dy * GetParentActor().GetModule<MovementDataModule>().stepSize;

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
        }

        GetParentActor().GetModule<MovementDataModule>().tickLastMove = Ticks();
    }

}  // namespace Forradia
