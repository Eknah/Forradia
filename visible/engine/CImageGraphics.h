#pragma once
#include "CommonExternal.h"
#include "../hidden/Aliases.h"

namespace Forradia
{

class CEngine;

class CImageGraphics
{

public:

    CImageGraphics(CEngine& engine) : Engine(engine) {}

    // Drawing operations
    void DrawImage(std::string imageName, float X, float Y, float width, float height);
    void DrawImage(int imageNameHash, float X, float Y, float width, float height);

private:

    CEngine& Engine;

};

}
