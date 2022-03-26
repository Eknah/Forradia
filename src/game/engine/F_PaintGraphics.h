
#pragma once
#include "CommonExternal.h"
#include "../core/F_Point2F.h"

namespace Forradia
{

class F_Engine;

class F_PaintGraphics
{

public:

    F_PaintGraphics(F_Engine& engine) : Engine(engine) {}

    // Drawing operations
    void FillRectangle(SDL_Color color, float X, float Y, float width, float height);
    void DrawRectangle(SDL_Color color, float X, float Y, float width, float height);
    void DrawLine(SDL_Color color, float x0, float y0, float x1, float y1);

private:

    // Drawing operations generalization
    void RenderShape(GLenum geometryType, std::vector<F_Point2F>& vertices, SDL_Color color);

    F_Engine& Engine;

};

}
