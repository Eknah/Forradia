// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include "Engine.h"
#include "RectF.h"
#include "Utilities.h"

namespace Forradia
{

    class GuiWindowBase
    {

        // Functions

    public:
        GuiWindowBase(Engine& _e, String _tile, RectF _bounds) : e(_e), title(_tile), bounds(_bounds) {}

        void Render();
        void Update();
        bool MouseDown(Uint8 button);
        void MouseUp();

    protected:
        RectF GetInnerBounds();

    private:
        RectF GetTopBarBounds();

        // Members

    public:
        bool visible = false;

    protected:
        virtual void MouseDownEx(Uint8 button) = 0;
        virtual void RenderEx() = 0;
        Engine& e;
        const float margin = 0.008f;

    private:
        Utilities utils;
        String title;
        RectF bounds;
        bool beingMoved = false;
        SDL_FPoint startMovePos = { -1, -1 };
        SDL_FPoint startMoveMousePos = { -1, -1 };

        const float topBarHeight = 0.04f;

    };

}