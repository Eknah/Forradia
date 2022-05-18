// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "PlanetShaper.h"
#include "Engine.h"
#include "CoreMovmModule.h"

namespace Forradia
{
    float PlanetShaper::GetNewY(float y, float tileX, float tileY)
    {

        auto result = y;

        auto dx = static_cast<int>(tileX) - e.GetPlayer().GetModule<CoreMovmModule>().position.x;
        auto dy = static_cast<int>(tileY) - e.GetPlayer().GetModule<CoreMovmModule>().position.y;
        auto distance = dx * dx + dy * dy;

        result -= distance * (0.01f/radius);

        return result;

    }
}