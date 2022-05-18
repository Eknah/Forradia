// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Utilities.h"
#include <iostream>

namespace Forradia
{

    Size Utilities::GetCanvasSize() const
    {
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        auto canvas_width = viewport[2];
        auto canvas_height = viewport[3];

        return { canvas_width, canvas_height };
    }
    Size Utilities::GetOrigCanvasSize() const
    {
        return origCanvasSize;
    }
    void Utilities::SetOrigCanvasSize(Size _size)
    {
        origCanvasSize = _size;
    }


    Point2 Utilities::GetMousePosI()
    {
        auto x = 0;
        auto y = 0;
        SDL_GetMouseState(&x, &y);

        return { x, y };
    }

    Point2F Utilities::GetMousePosF()
    {
        auto mousePosition = GetMousePosI();
        auto canvas_size = GetOrigCanvasSize();
        auto mousexF = static_cast<float>(mousePosition.x) / canvas_size.w;
        auto mouseyF = static_cast<float>(mousePosition.y) / canvas_size.h;

        return { mousexF, mouseyF };
    }

    SizeF Utilities::ConvertToFloat(int value)
    {
        auto canvasSize = GetOrigCanvasSize();
        auto resultWidth = static_cast<float>(value) / canvasSize.w;
        auto resultHeight = static_cast<float>(value) / canvasSize.h;

        return { resultWidth, resultHeight };
    }

}