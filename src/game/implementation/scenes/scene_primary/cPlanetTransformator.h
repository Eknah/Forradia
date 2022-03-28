// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

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
