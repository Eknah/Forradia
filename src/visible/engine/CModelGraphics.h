#pragma once
#include "CommonExternal.h"
#include "../hidden/Aliases.h"

namespace Forradia
{

class CEngine;

class CModelGraphics
{

public:

    CModelGraphics(CEngine& engine) : Engine(engine) {}

    // Drawing operations
    void DrawModel(std::string modelName, float x, float y, float z, float rotation = 0.0f, float specificScaling = 1.0f);
    void DrawModel(int modelNameHash, float x, float y, float z, float rotation = 0.0f, float specificScaling = 1.0f);

private:

    CEngine& Engine;

    float ModelScaling = 0.1f;
};

}
