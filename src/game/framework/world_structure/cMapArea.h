
#pragma once
#include "../engine/cPoint2F.h"
#include "cMob.h"
#include "../engine/Aliases.h"
#include "cTile.h"

namespace Forradia
{

class cEngine;

class cMapArea
{

public:

    cMapArea(cEngine& Engine, int mapAreaSize);

    // Basic data
    int Size = -1;
    cPoint2F PlayerSpawnPosition = {-1, -1};

    // Map structure of tiles and mobs
    std::vector<std::vector<cTile>> Tiles;
    std::vector<std::reference_wrapper<UPtr<cMob>>> MobsMirror;

};

}
