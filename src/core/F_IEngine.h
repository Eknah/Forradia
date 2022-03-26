
#pragma once
#include "framework/world_structure/F_MapArea.h"
#include "Typedefs.h"
#include "F_Vector3.h"
#include <SDL2/SDL.h>
#include "F_IKeyboardHandler.h"

namespace Forradia
{

class F_MapArea;

class F_IEngine
{

public:

    F_IEngine(F_IKeyboardHandler& KeyboardHandler_) : KeyboardHandler(KeyboardHandler_) {}

    virtual inline void DrawImage(std::string imageName, float x, float y, float width, float height)  = 0;
    virtual inline void DrawImage(int imageNameHash, float x, float y, float width, float height)  = 0;

    virtual inline void FillRectangle(SDL_Color color, float x, float y, float width, float height)  = 0;
    virtual inline void DrawRectangle(SDL_Color color, float X, float Y, float width, float height)  = 0;
    virtual inline void DrawLine(SDL_Color color, float x0, float y0, float x1, float y1) = 0;

    virtual inline void DrawString(std::string message, SDL_Color color, float x, float y, bool centerAlign = false)  = 0;

    virtual inline void DrawModel(std::string modelName, float x, float y, float z, float rotation = 0.0f, float specificScaling = 1.0f) = 0;
    virtual inline void DrawModel(int modelNameHash, float x, float y, float z, float rotation = 0.0f, float specificScaling = 1.0f) = 0;

    virtual inline F_MapArea& GetCurrentMapArea() = 0;

    F_WindowPtr Window;

    F_IKeyboardHandler&       KeyboardHandler;

};

}
