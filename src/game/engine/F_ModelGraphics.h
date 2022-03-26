
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

    // ---- Drawing operations ----

    void DrawModel(std::string ModelName, float X, float Y, float Z, float Rotation = 0.0f, float SpecificScaling = 1.0f);
    void DrawModel(int ModelNameId, float X, float Y, float Z, float Rotation = 0.0f, float SpecificScaling = 1.0f);

private:

    F_Engine& Engine;

    float ModelScaling = 0.1f;
};

}
