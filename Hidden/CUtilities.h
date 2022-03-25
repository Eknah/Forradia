#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "CSize.h"
#include "CPoint2.h"
#include "CPoint2F.h"
#include "CSizeF.h"
namespace Forradia
{

class CUtilities
{

public:
    inline CSize GetCanvasSize()
    {
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        auto canvas_width = viewport[2];
        auto canvas_height = viewport[3];
        return { canvas_width, canvas_height };
    }
    inline CPoint2 GetMousePositionI()
    {
        auto x = 0;
        auto y = 0;
        SDL_GetMouseState(&x, &y);
        return { x, y };
    }
    inline CPoint2F GetMousePositionF()
    {
        auto mouse_position = GetMousePositionI();
        auto canvas_size = GetCanvasSize();
        auto mouse_x_f = float(mouse_position.X) / canvas_size.Width;
        auto mouse_y_f = float(mouse_position.Y) / canvas_size.Height;
        return { mouse_x_f, mouse_y_f };
    }
    inline CSizeF ConvertToFloat(int value)
    {
        auto canvas_size = GetCanvasSize();
        auto result_width = float(value) / canvas_size.Width;
        auto result_height = float(value) / canvas_size.Height;
        return { result_width, result_height };
    }

};

}
