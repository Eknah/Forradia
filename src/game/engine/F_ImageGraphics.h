
#pragma once
#include "CommonExternal.h"
#include "../core/Aliases.h"

namespace Forradia
{

class F_Engine;

class F_ImageGraphics
{

public:

    F_ImageGraphics(F_Engine& engine) : Engine(engine) {}

    // Drawing operations
    void DrawImage(std::string ImageName, float X, float Y, float Width, float Height);
    void DrawImage(int ImageNameId, float X, float Y, float Width, float Height);

private:

    F_Engine& Engine;

};

}
