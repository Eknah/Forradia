#pragma once
#include "../hidden/CPoint2F.h"
#include "CMob.h"
#include "../hidden/Aliases.h"
#include "CTile.h"

namespace Forradia
{

class CEngine;

class CMapArea
{

public:

    CMapArea(CEngine& Engine, int mapAreaSize);

    // Basic data
    int Size = -1;
    bool IsCave = false;
    CPoint2F PlayerStartPosition = {-1, -1};

    // Map structure of tiles and mobs
    std::vector<std::vector<CTile>> Tiles;
    std::vector<std::reference_wrapper<UPtr<CMob>>> MobsMirror;

};

}
