
#pragma once
#include "CommonExternal.h"
#include "../engine/cEngine.h"

namespace Forradia
{

class cPlanetTransformator
{

public:

    cPlanetTransformator(cEngine& engine) : Engine(engine) {}

    float GetNewY(float tiley, float mapx, float mapy);

private:

    cEngine& Engine;
};

}
