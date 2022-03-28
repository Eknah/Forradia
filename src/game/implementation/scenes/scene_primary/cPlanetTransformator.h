// Copyright (C) 2022  Andreas Åkerberg

#pragma once
#include "CommonExternal.h"
#include "../engine/cEngine.h"

namespace Forradia
{

class cPlanetTransformator
{

public:

    cPlanetTransformator(cEngine& Engine_) : Engine(Engine_) {}

    float       GetNewY(float Y, float TileX, float TileY);

private:

    cEngine&    Engine;
};

}
