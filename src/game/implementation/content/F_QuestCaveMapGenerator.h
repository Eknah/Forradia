
#pragma once
#include "framework/world_structure/F_MapArea.h"
#include "../core/F_Point2.h"

namespace Forradia
{

class F_QuestCaveMapGenerator
{

public:

    void GenerateQuestCaveMapArea(F_MapArea& mapArea, F_Point2 entranceLocation, int warpFromMap);

private:

    void ClearToCaveFloor(F_MapArea& mapArea);
    void GenerateCaveWalls(F_MapArea& mapArea);
    void GeneratePath(F_MapArea& mapArea, F_Point2 entranceLocation);

};

}
