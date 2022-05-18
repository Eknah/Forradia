// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "Point2.h"
#include "Point2F.h"
#include "Size.h"
#include "SizeF.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace Forradia
{
    class Utilities
    {
    public:
        Size GetCanvasSize() const;
        Size GetOrigCanvasSize() const;
        void SetOrigCanvasSize(Size _size);
        Point2 GetMousePosI();
        Point2F GetMousePosF();
        SizeF ConvertToFloat(int value);

    private:
        static inline Size origCanvasSize = {0,0};
    };
}