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
        bool DoMouseDown(Uint8 MouseButton);
        void DoMouseUp();

        bool visible = false;

    protected:

        RectF GetInteriorBounds();

        virtual void DoMouseDownDerived(Uint8 MouseButton) = 0;
        virtual void RenderDerived() = 0;

        const Engine& e;
        const float margin = 0.008f;

    private:

        RectF GetTitleBarBounds();

        Palette palette;
        Utilities utilities;
        String title;
        RectF bounds;
        bool isBeingMoved = false;
        SDL_FPoint startMovePosition = { -1, -1 };
        SDL_FPoint startMoveMousePosition = { -1, -1 };

        const float titleBarHeight = 0.04f;
    };

}  // namespace Forradia
