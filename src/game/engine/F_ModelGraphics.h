#pragma once
#include "CommonExternal.h"
#include "../core/Aliases.h"

namespace Forradia
{

class F_Engine;

class F_ModelGraphics
{

public:

    F_ModelGraphics(F_Engine& engine) : Engine(engine) {}

    // Drawing operations
    void DrawModel(std::string modelName, float x, float y, float z, float rotation = 0.0f, float specificScaling = 1.0f);
    void DrawModel(int modelNameHash, float x, float y, float z, float rotation = 0.0f, float specificScaling = 1.0f);

private:

    F_Engine& Engine;

    float ModelScaling = 0.1f;
};

}
