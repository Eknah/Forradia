
#pragma once
#include "framework/iMapGenerator.h"
#include "framework/world_structure/cMapArea.h"

namespace Forradia
{

class cDefaultMapGenerator : public iMapGenerator
{

public:

    using iMapGenerator::iMapGenerator;

    void GenerateMapArea(int WorldX, int WorldY, int WorldZ) override;

private:

    void ClearToGrass(cMapArea& mapArea);
    void GeneratePlayerStartingPosition(cMapArea& mapArea);
    void GenerateElevation(cMapArea& mapArea);
    void GenerateWater(cMapArea& mapArea);
    void GenerateSand(cMapArea& mapArea);
    void GenerateClay(cMapArea& mapArea);
    void GenerateRock(cMapArea& mapArea);
    void GenerateTrees(cMapArea& mapArea);
    void GenerateBushes(cMapArea& mapArea);
    void GenerateSmallStones(cMapArea& mapArea);
    //void GenerateTallGrass(F_MapArea& mapArea);
    void GeneratePinkFlowers(cMapArea& mapArea);
    void GenerateMobs(cMapArea& mapArea);
    void GenerateQuestCaves(cEngine& Engine, cMapArea& mapArea, UPtr<cWorldMap>& WorldMap);
    int DistToPlayerStartingPos(cMapArea& mapArea, int mapX, int mapY);

    const int PlayerStartingAreaSize = 4;

};

}
