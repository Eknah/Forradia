// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "WarpMovementModule.h"
#include "../engine/IEngine.h"
#include "CoreMovementModule.h"

namespace Forradia
{

    void WarpMovementModule::WarpIfStandOnPortal()
    {
        auto& coreMovement = GetParentActor().GetModule<CoreMovementModule>();

        auto newx = coreMovement.position.x;
        auto newy = coreMovement.position.y;

        if (e.GetCurrMapArea().tiles[CInt(newx)][CInt(newy)].properties.count("WarpToFloor") > 0)
        {
            auto angle = *coreMovement.facingAngle / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
            auto dx = -std::cos(angle) * coreMovement.stepMultiplier;
            auto dy = std::sin(angle) * coreMovement.stepMultiplier;

            auto newXOld = newx;
            auto newYOld = newy;

            newx += dx * coreMovement.stepSize * 10;
            newy += dy * coreMovement.stepSize * 10;

            auto oldXI = CInt(coreMovement.position.x);
            auto oldYI = CInt(coreMovement.position.y);

            coreMovement.position.x = newx;
            coreMovement.position.y = newy;

            auto coord = e.GetCurrMapArea().worldCoord;
            coord.z = std::stoi(e.GetCurrMapArea().tiles[CInt(newXOld)][CInt(newYOld)].properties.at("WarpToFloor"));

            e.world->GetArea(coord)->tiles[newx][newy].actor = std::move(e.GetCurrMapArea().tiles[newXOld][newYOld].actor);
            e.GetCurrMapArea().tiles[newXOld][newYOld].actor = nullptr;

            coreMovement.worldMapCoord.z = std::stoi(e.GetCurrMapArea().tiles[CInt(newXOld)][CInt(newYOld)].properties.at("WarpToFloor"));
        }
    }

}  // namespace Forradia
