// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "WarpMovementModule.h"
#include "../engine/IEngine.h"
#include "CoreMovementModule.h"

namespace Forradia
{

    void WarpMovementModule::WarpIfStandOnPortal()
    {
        auto& coreMovm = GetParentActor().GetModule<CoreMovementModule>();

        auto newx = coreMovm.position.x;
        auto newy = coreMovm.position.y;

        if (e.GetCurrMapArea().tiles[CInt(newx)][CInt(newy)].properties.count("WarpToFloor") > 0)
        {
            auto angle = *coreMovm.facingAngle / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
            auto dx = -std::cos(angle) * coreMovm.stepMultiplier;
            auto dy = std::sin(angle) * coreMovm.stepMultiplier;

            auto newXOld = newx;
            auto newYOld = newy;

            newx += dx * coreMovm.stepSize * 10;
            newy += dy * coreMovm.stepSize * 10;

            auto oldXI = CInt(coreMovm.position.x);
            auto oldYI = CInt(coreMovm.position.y);

            coreMovm.position.x = newx;
            coreMovm.position.y = newy;

            auto coord = e.GetCurrMapArea().worldCoord;
            coord.z = std::stoi(e.GetCurrMapArea().tiles[CInt(newXOld)][CInt(newYOld)].properties.at("WarpToFloor"));

            e.world->GetArea(coord)->tiles[newx][newy].actor = std::move(e.GetCurrMapArea().tiles[newXOld][newYOld].actor);
            e.GetCurrMapArea().tiles[newXOld][newYOld].actor = nullptr;

            coreMovm.worldMapCoord.z = std::stoi(e.GetCurrMapArea().tiles[CInt(newXOld)][CInt(newYOld)].properties.at("WarpToFloor"));
        }
    }

}  // namespace Forradia
