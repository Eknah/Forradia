// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Engine.h"
#include "../engine/Utilities.h"

namespace Forradia
{

    class GuiMinimap
    {
    public:
        explicit GuiMinimap(const Engine& _e) : e(_e) {}

        void Render();

    private:
        const Engine& e;

        const int minimapSize = 250;
        Palette palette;
        Utilities utilities;
    };

}  // namespace Forradia
