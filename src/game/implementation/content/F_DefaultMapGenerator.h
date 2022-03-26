#pragma once
#include "framework/F_IMapGenerator.h"
#include "framework/world_structure/F_MapArea.h"

namespace Forradia
{

class F_DefaultMapGenerator : public F_IMapGenerator
{

public:

    using F_IMapGenerator::F_IMapGenerator;

    void GenerateMapArea(F_Point2 worldMapCoord) override;

private:

    void ClearToGrass(F_MapArea& mapArea);
    void GeneratePlayerStartingPosition(F_MapArea& mapArea);
    void GenerateElevation(F_MapArea& mapArea);
    void GenerateWater(F_MapArea& mapArea);
    void GenerateSand(F_MapArea& mapArea);
    void GenerateClay(F_MapArea& mapArea);
    void GenerateRock(F_MapArea& mapArea);
    void GenerateTrees(F_MapArea& mapArea);
    void GenerateBushes(F_MapArea& mapArea);
    void GenerateSmallStones(F_MapArea& mapArea);
    void GenerateTallGrass(F_MapArea& mapArea);
    void GeneratePinkFlowers(F_MapArea& mapArea);
    void GenerateMobs(F_MapArea& mapArea);
    void GenerateQuestCaves(F_Engine& Engine, F_MapArea& mapArea, UPtr<F_WorldMap>& WorldMap);
    int DistToPlayerStartingPos(F_MapArea& mapArea, int mapX, int mapY);

    const int PlayerStartingAreaSize = 4;

};

}
