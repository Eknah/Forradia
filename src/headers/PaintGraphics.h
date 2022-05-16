// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <GL/glew.h>
#include <SDL2/SDL_pixels.h>
#include <vector>
#include "Point2F.h"
#include "RectF.h"
#include "LineF.h"

namespace Forradia
{

    class PaintGraphics {
    public:
        // ---- Drawing operations ----

        void FillRect(SDL_Color color, RectF rect) const;
        void DrawRect(SDL_Color color, RectF rect) const;
        void FillRect(SDL_Color color, float x, float y, float w, float Height) const;
        void DrawRect(SDL_Color color, float x, float y, float w, float h) const;
        void DrawLine(SDL_Color color, LineF line) const;
        void DrawLine(SDL_Color color, float x0, float y0, float x1, float y1) const;

    private:
        // ---- Drawing operations generalization ----

        void RenderShape(GLenum geometryType, const std::vector<Point2F>& vertices, SDL_Color color) const;
    };

}  // namespace Forradia
