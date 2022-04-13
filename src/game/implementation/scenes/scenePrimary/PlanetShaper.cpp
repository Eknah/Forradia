// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "PlanetShaper.h"
#include "../engine/Engine.h"
#include "implementation/functionality/actor/modules/MovementDataModule.h"

namespace Forradia
{

    float PlanetShaper::GetNewY(float y, float tileX, float tileY)
    {
        return y;
        auto result = y;
        auto dx = static_cast<int>(tileX) - e.GetPlayer().GetModule<CoreMovementModule>().position.x;
        auto dy = static_cast<int>(tileY) - e.GetPlayer().GetModule<CoreMovementModule>().position.y;
        auto distance = dx * dx + dy * dy;

        result -= distance * 0.01f;

        return result;
    }

}  // namespace Forradia
