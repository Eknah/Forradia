// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "PaintGraphics.h"

namespace Forradia
{

    void PaintGraphics::FillRectangle(SDL_Color Color, float X, float Y, float Width, float Height) const
    {
        std::vector<Point2F> vertices = {
            {X, Y}, {X, Y + Height}, {X + Width, Y + Height}, {X + Width, Y} };

        RenderShape(GL_QUADS, vertices, Color);
    }

    void PaintGraphics::DrawRectangle(SDL_Color Color, float X, float Y, float Width, float Height) const
    {
        std::vector<Point2F> vertices = {
            {X, Y}, {X, Y + Height}, {X + Width, Y + Height}, {X + Width, Y} };

        RenderShape(GL_LINE_LOOP, vertices, Color);
    }

    void PaintGraphics::DrawLine(SDL_Color Color, float X0, float Y0, float X1, float Y1) const
    {
        std::vector<Point2F> vertices = { {X0, Y0}, {X1, Y1} };

        RenderShape(GL_LINE_STRIP, vertices, Color);
    }

    void PaintGraphics::RenderShape(GLenum GeometryType, const std::vector<Point2F>& Vertices, SDL_Color Color) const
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);

        glBegin(GeometryType);

        glColor4f(Color.r / 255.0f, Color.g / 255.0f, Color.b / 255.0f,
            Color.a / 255.0f);

        for (auto& Vertex : Vertices)
            glVertex2f(Vertex.x, Vertex.y);

        glEnd();
    }

}  // namespace Forradia
