// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "Engine.h"
#include "Background.h"
#include "Camera.h"
#include "PlanetShaper.h"
#include <array>

namespace Forradia
{

    class WorldRenderer
    {

    public:

        WorldRenderer(const Engine& _e, const Camera& _camera)
            : e(_e), background(_e), planetShaper(_e), cam(_camera)
        {}

        void Render();

    private:

        void DoRender();
        void RenderRoof(int x, int y);
        float CalcPlayerElev();
        Point2F CalcOffset();

        int RES_WIDTH = 250;
        int RES_HEIGHT = 150;
         unsigned int rbo;
        Utilities utilities;
        Size origCanvasSize;
        GLuint fbo;
        GLuint renderedTexture;
        bool initialized = false;
        const Engine& e;
        Background background;
        const Camera& cam;
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
