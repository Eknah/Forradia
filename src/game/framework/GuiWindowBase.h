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
        bool DoMouseDown(Uint8 button);
        void DoMouseUp();

        bool visible = false;

    protected:

        RectF GetInteriorBounds();

        virtual void DoMouseDownDerived(Uint8 button) = 0;
        virtual void RenderDerived() = 0;

        const Engine& e;
        const float margin = 0.008f;

    private:

        RectF GetTopBarBounds();

        Palette palette;
        Utilities utils;
        String title;
        RectF bounds;
        bool isBeingMoved = false;
        SDL_FPoint startMovePos = { -1, -1 };
        SDL_FPoint startMoveMousePos = { -1, -1 };

        const float topBarHeight = 0.04f;
    };

}  // namespace Forradia
