// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Engine.h"
#include "Background.h"
#include "Camera.h"
#include "PlanetShaper.h"
#include <array>

namespace Forradia
{

    class GameWorldRenderer
    {

    public:

        GameWorldRenderer(const Engine& _e, const Camera& _camera)
            : e(_e), background(_e), planetShaper(_e),
            camera(_camera)
        {}

        void Render();

    private:
        void RenderAllExceptRoofAndRays();
        void RenderRoofAndRays();
        float CalcPlayerElev();
        Point2F CalcOffset();

        const Engine& e;
        Background background;
        const Camera& camera;
        PlanetShaper planetShaper;
        const int groundTypeWaterId = GetId("GroundTypeWater");
        float elevAmount = 5.0f;
        std::array<float, 4> GetElevValues(int tilexI, int tileyI);

        const int animWaterId[4] =
        {
          GetId("GroundTypeWater"),
          GetId("GroundTypeWater1"),
          GetId("GroundTypeWater2"),
          GetId("GroundTypeWater3")
        };

    };

}  // namespace Forradia
