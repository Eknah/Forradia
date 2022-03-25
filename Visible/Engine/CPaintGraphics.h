#pragma once
#include "CommonExternal.h"
#include "../Hidden/CPoint2F.h"

namespace Forradia
{

class CEngine;

class CPaintGraphics
{

public:

    CPaintGraphics(CEngine& engine) : Engine(engine) {}

    // Drawing operations
    void FillRectangle(SDL_Color color, float X, float Y, float width, float height);
    void DrawRectangle(SDL_Color color, float X, float Y, float width, float height);
    void DrawLine(SDL_Color color, float x0, float y0, float x1, float y1);

private:

    // Drawing operations generalization
    void RenderShape(GLenum geometryType, std::vector<CPoint2F>& vertices, SDL_Color color);

    CEngine& Engine;

};

}
