// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "WarpMovementModule.h"
#include "../engine/IEngine.h"
#include "MovementDataModule.h"

namespace Forradia
{

    void WarpMovementModule::WarpIfStandOnPortal()
    {
        auto newX = GetParentActor().GetModule<CoreMovementModule>().position.x;
        auto newY = GetParentActor().GetModule<CoreMovementModule>().position.y;

        if (e.GetCurrentMapArea().tiles
            [static_cast<int>(newX)][static_cast<int>(newY)].properties.count("WarpToFloor") > 0)
        {
            auto angle = *GetParentActor().GetModule<CoreMovementModule>().facingAngle
                / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
            auto dx = -static_cast<float>(std::cos(angle)) * GetParentActor().GetModule<CoreMovementModule>().stepMultiplier;
            auto dy = static_cast<float>(std::sin(angle)) * GetParentActor().GetModule<CoreMovementModule>().stepMultiplier;

            auto newXOld = newX;
            auto newYOld = newY;

            newX += dx * GetParentActor().GetModule<CoreMovementModule>().stepSize * 10;
            newY += dy * GetParentActor().GetModule<CoreMovementModule>().stepSize * 10;

            auto oldXI = static_cast<int>(GetParentActor().GetModule<CoreMovementModule>().position.x);
            auto oldYI = static_cast<int>(GetParentActor().GetModule<CoreMovementModule>().position.y);

            GetParentActor().GetModule<CoreMovementModule>().position.x = newX;
            GetParentActor().GetModule<CoreMovementModule>().position.y = newY;

            auto coord = e.GetCurrentMapArea().worldCoord;
            coord.z = std::stoi(e.GetCurrentMapArea().tiles
                [static_cast<int>(newXOld)][static_cast<int>(newYOld)].properties.at("WarpToFloor"));

            e.world->GetArea(coord)->tiles[newX][newY].actor
                = std::move(e.GetCurrentMapArea().tiles[newXOld][newYOld].actor);
            e.GetCurrentMapArea().tiles[newXOld][newYOld].actor = nullptr;

            GetParentActor().GetModule<CoreMovementModule>().worldMapCoord.z =
                std::stoi(e.GetCurrentMapArea().tiles
                    [static_cast<int>(newXOld)][static_cast<int>(newYOld)].properties.at("WarpToFloor"));
        }
    }

}  // namespace Forradia
