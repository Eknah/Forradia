#pragma once
#include "framework/world_structure/CMapArea.h"
#include "../hidden/CPoint2.h"

namespace Forradia
{

class CQuestCaveMapGenerator
{

public:

    void GenerateQuestCaveMapArea(CMapArea& mapArea, CPoint2 entranceLocation, int warpFromMap);

private:

    void ClearToCaveFloor(CMapArea& mapArea);
    void GenerateCaveWalls(CMapArea& mapArea);
    void GeneratePath(CMapArea& mapArea, CPoint2 entranceLocation);

};

}
