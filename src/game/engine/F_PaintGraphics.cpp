
#include "CommonExternal.h"
#include "F_PaintGraphics.h"

namespace Forradia
{

void F_PaintGraphics::FillRectangle(SDL_Color Color, float X, float Y, float Width, float Height)
{
    std::vector<F_Point2F> vertices =
    {
        {X,Y},
        {X, Y + Height},
        {X + Width, Y + Height},
        {X + Width, Y}
    };

    RenderShape(GL_QUADS, vertices, Color);
}

void F_PaintGraphics::DrawRectangle(SDL_Color Color, float X, float Y, float Width, float Height)
{
    std::vector<F_Point2F> vertices =
    {
        {X,Y},
        {X, Y + Height},
        {X + Width, Y + Height},
        {X + Width, Y}
    };

    RenderShape(GL_LINE_LOOP, vertices, Color);
}

void F_PaintGraphics::DrawLine(SDL_Color Color, float X0, float Y0, float X1, float Y1)
{
    std::vector<F_Point2F> vertices =
    {
        {X0,Y0},
        {X1, Y1}
    };

    RenderShape(GL_LINE_STRIP, vertices, Color);
}

void F_PaintGraphics::RenderShape(GLenum GeometryType, std::vector<F_Point2F>& Vertices, SDL_Color Color)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);

    glBegin(GeometryType);

    glColor4f(Color.r / 255.0f, Color.g / 255.0f, Color.b / 255.0f, Color.a / 255.0f);

    for (auto& Vertex : Vertices)
        glVertex2f(Vertex.X, Vertex.Y);

    glEnd();
}

}
