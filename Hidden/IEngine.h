#pragma once
#include "Framework/WorldStructure/CMapArea.h"
#include "CVector3.h"
#include <SDL2/SDL.h>

namespace Forradia
{

class IEngine
{
public:
    virtual inline void DrawImage(String imageName, float x, float y, float width, float height)  = 0;
    virtual inline void DrawImage(int imageNameHash, float x, float y, float width, float height)  = 0;

    virtual inline void FillRectangle(SDL_Color color, float x, float y, float width, float height)  = 0;
    virtual inline void DrawRectangle(SDL_Color color, float X, float Y, float width, float height)  = 0;
    virtual inline void DrawLine(SDL_Color color, float x0, float y0, float x1, float y1) = 0;

    virtual inline void DrawString(String message, SDL_Color color, float x, float y, bool centerAlign = false)  = 0;

    virtual inline void DrawModel(String modelName, float x, float y, float z, float rotation = 0.0f, float alpha = 1.0f, float specificScaling = 1.0f, CVector3 rotVec = CVector3(0, 0, 0)) = 0;
    virtual inline void DrawModel(int modelNameHash, float x, float y, float z, float rotation = 0.0f, float alpha = 1.0f, float specificScaling = 1.0f, CVector3 rotVec = CVector3(0, 0, 0)) = 0;

    virtual inline CMapArea& GetCurrentMapArea() = 0;


    SDL_Window* GWindow = NULL;
};

}
