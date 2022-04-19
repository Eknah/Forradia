// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include "../engine/Engine.h"
#include "../engine/RectF.h"
#include "../engine/Utilities.h"

namespace Forradia
{

    class GuiWindowBase
    {

    public:

        GuiWindowBase(const Engine& _e, String _tile, RectF _bounds) : e(_e), title(_tile), bounds(_bounds)
        {}

        void Render();
        void Update();
        bool MouseDown(Uint8 button);
        void MouseUp();

        bool visible = false;

    protected:

        RectF GetInnerBounds();

        virtual void MouseDownEx(Uint8 button) = 0;
        virtual void RenderEx() = 0;

        const Engine& e;
        const float margin = 0.008f;

    private:

        RectF GetTopBarBounds();

        Palette pal;
        Utilities utils;
        String title;
        RectF bounds;
        bool beingMoved = false;
        SDL_FPoint startMovePos = { -1, -1 };
        SDL_FPoint startMoveMousePos = { -1, -1 };

        const float topBarHeight = 0.04f;
    };

}  // namespace Forradia
