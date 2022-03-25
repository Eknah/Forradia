#include "CQuestCaveMapGenerator.h"
namespace Forradia
{
void CQuestCaveMapGenerator::GenerateQuestCaveMapArea(CMapArea& mapArea, CPoint2 entranceLocation, int warpFromMap)
{
    mapArea.IsCave = true;
    ClearToCaveFloor(mapArea);
    GenerateCaveWalls(mapArea);
    GeneratePath(mapArea, entranceLocation);
    mapArea.Tiles[entranceLocation.X][entranceLocation.Y].WarpToMap = warpFromMap;
    mapArea.Tiles[entranceLocation.X][entranceLocation.Y].Objects.push_back(MakeUPtr<CObject>("ObjectQuestCaveEntrance"));
}
void CQuestCaveMapGenerator::ClearToCaveFloor(CMapArea& mapArea)
{
    for (auto y = 0; y < mapArea.Size; y++)
        for (auto x = 0; x < mapArea.Size; x++)
            mapArea.Tiles[x][y].GroundType = GetId("GroundtypeCaveFloor");
}
void CQuestCaveMapGenerator::GenerateCaveWalls(CMapArea& mapArea)
{
    for (auto y = 0; y < mapArea.Size; y++)
        for (auto x = 0; x < mapArea.Size; x++)
            mapArea.Tiles[x][y].Objects.push_back(MakeUPtr<CObject>("ObjectCaveWallBlock", false));
}
void CQuestCaveMapGenerator::GeneratePath(CMapArea& mapArea, CPoint2 entranceLocation)
{
    for (auto y = entranceLocation.Y - 3; y <= entranceLocation.Y + 3; y++)
        for (auto x = entranceLocation.X - 3; x <= entranceLocation.X + 3; x++)
            mapArea.Tiles[x][y].Objects.clear();
    auto x = entranceLocation.X;
    auto y = entranceLocation.Y;
    for (auto i = 0; i < 20; i++)
    {
        auto direction = rand() % 4;
        auto num_steps = 4 + rand() % 20;
        for (auto j = 0; j < num_steps; j++)
        {
            for (auto xx = x - 1; xx <= x + 1; xx++)
            {
                for (auto yy = y - 1; yy <= y + 1; yy++)
                {
                    if (xx >= 0 && yy >= 0 && xx < mapArea.Size && yy < mapArea.Size)
                        if (mapArea.Tiles[xx][yy].Objects.size() > 0)
                            if (!mapArea.Tiles[xx][yy].HasObjectOfType("ObjectQuestCaveEntrance"))
                                mapArea.Tiles[xx][yy].Objects.clear();
                }
            }
            switch (direction)
            {
            case 0:
            {
                x++;
                break;
            }
            case 1:
            {
                y++;
                break;
            }
            case 2:
            {
                x--;
                break;
            }
            case 3:
            {
                y--;
                break;
            }
            }
        }
    }
}
}
