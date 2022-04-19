// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include <vector>
#include "../engine/Engine.h"
#include "../engine/Utilities.h"
#include "Minimap.h"
#include "framework/GuiWindowBase.h"
#include "os/Console.h"

namespace Forradia
{

    class Gui
    {
    public:

        explicit Gui(const Engine& _e) : e(_e), minimap(_e), console(_e)
        {}

        void Init();
        void Update();
        void Render();
        bool MouseDown(Uint8 mouseButton);
        void MouseUp();
        void KeyDown(SDL_Keycode key);

        UMap<String, UPtr<GuiWindowBase>> windows;
        Console console;

    private:

        const Engine& e;

        Minimap minimap;
        const float margin = 0.005f;
        Utilities utils;
        const float btnWidth = 0.15f;
        const float btnHeight = 0.03f;
        RectF boundsCharBtn = { 0.0f, 1.0f - btnHeight, btnWidth, btnHeight };
        RectF boundsInvBtn = { btnWidth,             1.0f - btnHeight, btnWidth, btnHeight };
        RectF boundsSysBtn = { 2*btnWidth,  1.0f - btnHeight, btnWidth, btnHeight };
        Palette pal;

    };

}  // namespace Forradia
