// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "Engine.h"
#include "Utilities.h"
#include "Camera.h"

namespace Forradia
{

    class RightClickMenu
    {

    public:

        explicit RightClickMenu(Engine& _e, Camera& _camera) : e(_e), camera(_camera) {}


        void Render();
        void MouseDown(Uint8 mouseButton);
        void MouseUp(Uint8 mouseButton);

    private:

        Engine& e;

        bool visible = false;
        Point2F mouseClickPos = {-1, -1};
        Utilities utils;
        const float width = 0.1f;
        const float lineHeight = 0.02f;
        Camera& camera;
        std::vector<CraftRecipe> recipes;

    };

}