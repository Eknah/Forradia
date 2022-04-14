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
        bool DoMouseDown(Uint8 mouseButton);
        void DoMouseUp();
        void DoKeyDown(SDL_Keycode key);

        UMap<String, UPtr<GuiWindowBase>> windows;
        Console console;

    private:

        const Engine& e;

        Minimap minimap;
        const float margin = 0.005f;
        Utilities utils;
        const float btnWidth = 0.15f;
        const float btnHeight = 0.03f;
        RectF boundsInvBtn = { 0.5f - btnWidth / 2, 1.0f - btnHeight, btnWidth, btnHeight };
        RectF boundsCharBtn = { 0.5f - btnWidth / 2 - btnWidth, 1.0f - btnHeight, btnWidth, btnHeight };
        RectF boundsSysBtn = { 0.5f - btnWidth / 2 + btnWidth, 1.0f - btnHeight, btnWidth, btnHeight };
        Palette palette;

    };

}  // namespace Forradia
