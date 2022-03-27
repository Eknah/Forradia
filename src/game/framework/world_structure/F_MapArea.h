
#pragma once
#include "../engine/F_Point2F.h"
#include "F_Mob.h"
#include "../engine/Aliases.h"
#include "F_Tile.h"

namespace Forradia
{

class F_Engine;

class F_MapArea
{

public:

    F_MapArea(F_Engine& Engine, int mapAreaSize);

    // Basic data
    int Size = -1;
    bool IsCave = false;
    F_Point2F PlayerStartPosition = {-1, -1};

    // Map structure of tiles and mobs
    std::vector<std::vector<F_Tile>> Tiles;
    std::vector<std::reference_wrapper<UPtr<F_Mob>>> MobsMirror;

};

}
