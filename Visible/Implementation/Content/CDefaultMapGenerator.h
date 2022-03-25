#pragma once
namespace Forradia
{

class CDefaultMapGenerator : public IMapGenerator
{

public:
    using IMapGenerator::IMapGenerator;

    void GenerateMapArea(CPoint2 worldMapCoord) override;

private:
    void ClearToGrass(CMapArea& mapArea);
    void GeneratePlayerStartingPosition(CMapArea& mapArea);
    void GenerateElevation(CMapArea& mapArea);
    void GenerateWater(CMapArea& mapArea);
    void GenerateSand(CMapArea& mapArea);
    void GenerateClay(CMapArea& mapArea);
    void GenerateRock(CMapArea& mapArea);
    void GenerateTrees(CMapArea& mapArea);
    void GenerateBushes(CMapArea& mapArea);
    void GenerateSmallStones(CMapArea& mapArea);
    void GenerateTallGrass(CMapArea& mapArea);
    void GeneratePinkFlowers(CMapArea& mapArea);
    void GenerateMobs(CMapArea& mapArea);
    void GenerateQuestCaves(CEngine& Engine, CMapArea& mapArea, UPtr<CWorldMap>& WorldMap);
    int DistToPlayerStartingPos(CMapArea& mapArea, int mapX, int mapY);

    const int PlayerStartingAreaSize = 4;

};

}
