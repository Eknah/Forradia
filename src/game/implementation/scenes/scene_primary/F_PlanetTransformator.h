#pragma once
#include "CommonExternal.h"
#include "../core/F_Engine.h"

namespace Forradia
{

class F_PlanetTransformator
{

public:

    F_PlanetTransformator(F_Engine& engine) : Engine(engine) {}

    float GetNewY(float tiley, float mapx, float mapy);

private:

    F_Engine& Engine;
};

}
