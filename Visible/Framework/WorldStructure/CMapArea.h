#pragma once
#include "../Hidden/CPoint2F.h"
#include "CMob.h"
#include "../Hidden/Aliases.h"
#include "CTile.h"
namespace Forradia
{

class CMapArea
{

public:

    CMapArea(CEngine& Engine, int mapAreaSize);

    // Basic data
    int Size = -1;
    bool IsCave = false;
    CPoint2F PlayerStartPosition = {-1, -1};

    // Map structure of tiles and mobs
    List<List<CTile>> Tiles;
    List<std::reference_wrapper<UPtr<CMob>>> MobsMirror;

};

}
