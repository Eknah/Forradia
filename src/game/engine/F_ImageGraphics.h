
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
    void DrawImage(std::string imageName, float X, float Y, float width, float height);
    void DrawImage(int imageNameHash, float X, float Y, float width, float height);

private:

    F_Engine& Engine;

};

}
