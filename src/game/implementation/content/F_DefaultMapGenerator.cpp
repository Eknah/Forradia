
#include "F_DefaultMapGenerator.h"
#include "F_QuestCaveMapGenerator.h"
#include "framework/world_structure/F_WorldMap.h"

namespace Forradia
{

void F_DefaultMapGenerator::GenerateMapArea(F_Point2 worldMapCoord)
{
    WorldMap->MapAreas.push_back(MakeUPtr<F_MapArea>(Engine, WorldMap->MapAreaSize));

    auto map_area_id = WorldMap->MapAreas.size() - 1;
    auto& map_area = *WorldMap->MapAreas.at(map_area_id);

    ClearToGrass(map_area);
    GeneratePlayerStartingPosition(map_area);
    GenerateElevation(map_area);
    GenerateWater(map_area);
    GenerateSand(map_area);
    GenerateClay(map_area);
    GenerateRock(map_area);
    GenerateTrees(map_area);
    GenerateBushes(map_area);
    GenerateSmallStones(map_area);
    //GenerateTallGrass(map_area);
    GeneratePinkFlowers(map_area);
    GenerateMobs(map_area);
    GenerateQuestCaves(Engine, map_area, WorldMap);
}

void F_DefaultMapGenerator::ClearToGrass(F_MapArea& mapArea)
{
    for (auto y = 0; y < mapArea.Size; y++)
        for (auto x = 0; x < mapArea.Size; x++)
            mapArea.Tiles[x][y].GroundType = (int)GetId("GroundtypeGrass");
}

void F_DefaultMapGenerator::GeneratePlayerStartingPosition(F_MapArea& mapArea)
{
    mapArea.PlayerStartPosition.X = rand() % mapArea.Size;
    mapArea.PlayerStartPosition.Y = rand() % mapArea.Size;
}

void F_DefaultMapGenerator::GenerateElevation(F_MapArea& mapArea)
{
    for (auto i = 0; i < 40; i++)
    {
        auto x_center = rand() % mapArea.Size;
        auto y_center = rand() % mapArea.Size;
        auto r_max = 4 + rand() % 12;
        for (auto r = r_max; r >= 0; r--)
        {
            for (auto y = y_center - r; y <= y_center + r; y++)
            {
                for (auto x = x_center - r; x <= x_center + r; x++)
                {
                    auto dx = x - x_center;
                    auto dy = y - y_center;

                    if (dx * dx + dy * dy >= r * r) continue;
                    if (x < 0 || y < 0 || x >= mapArea.Size || y >= mapArea.Size) continue;

                    mapArea.Tiles[x][y].Elevation += 2;
                }
            }
        }
    }

    for (auto i = 0; i < 1000; i++)
    {
        auto x = rand() % mapArea.Size;
        auto y = rand() % mapArea.Size;

        mapArea.Tiles[x][y].Elevation += 2 - rand() % 5;
    }
}

void F_DefaultMapGenerator::GenerateWater(F_MapArea& mapArea)
{
    for (auto i = 0; i < 20; i++)
    {
        auto x_center = rand() % mapArea.Size;
        auto y_center = rand() % mapArea.Size;
        auto r = 5 + rand() % 13;

        for (auto y = y_center - r; y <= y_center + r; y++)
        {
            for (auto x = x_center - r; x <= x_center + r; x++)
            {
                auto dx = x - x_center;
                auto dy = y - y_center;

                if (dx * dx + dy * dy >= r * r) continue;
                if (x <= 0 || y <= 0 || x >= mapArea.Size - 1 || y >= mapArea.Size - 1) continue;
                if (mapArea.Tiles[x][y].Elevation > 0) continue;
                if (mapArea.Tiles[x - 1][y].Elevation > 0) continue;
                if (mapArea.Tiles[x - 1][y - 1].Elevation > 0) continue;
                if (mapArea.Tiles[x][y - 1].Elevation > 0) continue;
                if (mapArea.Tiles[x + 1][y].Elevation > 0) continue;
                if (mapArea.Tiles[x + 1][y + 1].Elevation > 0) continue;
                if (mapArea.Tiles[x][y + 1].Elevation > 0) continue;
                if (mapArea.Tiles[x - 1][y + 1].Elevation > 0) continue;
                if (mapArea.Tiles[x + 1][y - 1].Elevation > 0) continue;
                if (DistToPlayerStartingPos(mapArea, x, y) < PlayerStartingAreaSize) continue;

                mapArea.Tiles[x][y].GroundType = (int)GetId("GroundtypeWater");
            }
        }
    }
}

void F_DefaultMapGenerator::GenerateSand(F_MapArea& mapArea)
{
    for (auto i = 0; i < 30; i++)
    {
        auto x_center = rand() % mapArea.Size;
        auto y_center = rand() % mapArea.Size;
        auto r = 4 + rand() % 5;

        for (auto i = 0; i < r; i++)
        {
            for (auto y = y_center - r; y <= y_center + r; y++)
            {
                for (auto x = x_center - r; x <= x_center + r; x++)
                {
                    auto dx = x - x_center;
                    auto dy = y - y_center;

                    if (dx * dx + dy * dy >= r * r) continue;
                    if (x <= 0 || y <= 0 || x >= mapArea.Size - 1 || y >= mapArea.Size - 1) continue;
                    if (mapArea.Tiles[x][y].GroundType == (int)GetId("GroundtypeWater")) continue;
                    if (mapArea.Tiles[x][y].Elevation > 5) continue;

                    if (
                            mapArea.Tiles[x - 1][y].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x - 1][y].GroundType != (int)GetId("GroundtypeSand") &&
                            mapArea.Tiles[x - 1][y - 1].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x - 1][y - 1].GroundType != (int)GetId("GroundtypeSand") &&
                            mapArea.Tiles[x][y - 1].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x][y - 1].GroundType != (int)GetId("GroundtypeSand") &&
                            mapArea.Tiles[x + 1][y - 1].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x + 1][y - 1].GroundType != (int)GetId("GroundtypeSand") &&
                            mapArea.Tiles[x + 1][y].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x + 1][y].GroundType != (int)GetId("GroundtypeSand") &&
                            mapArea.Tiles[x + 1][y + 1].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x + 1][y + 1].GroundType != (int)GetId("GroundtypeSand") &&
                            mapArea.Tiles[x][y + 1].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x][y + 1].GroundType != (int)GetId("GroundtypeSand") &&
                            mapArea.Tiles[x - 1][y + 1].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x - 1][y + 1].GroundType != (int)GetId("GroundtypeSand")
                            )
                        continue;

                    mapArea.Tiles[x][y].GroundType = (int)GetId("GroundtypeSand");
                }
            }
        }
    }
}

void F_DefaultMapGenerator::GenerateClay(F_MapArea& mapArea)
{
    for (auto i = 0; i < 30; i++)
    {
        auto x_center = rand() % mapArea.Size;
        auto y_center = rand() % mapArea.Size;
        auto r = 2 + rand() % 3;

        for (auto i = 0; i < r; i++)
        {
            for (auto y = y_center - r; y <= y_center + r; y++)
            {
                for (auto x = x_center - r; x <= x_center + r; x++)
                {
                    auto dx = x - x_center;
                    auto dy = y - y_center;

                    if (dx * dx + dy * dy >= r * r) continue;
                    if (x <= 0 || y <= 0 || x >= mapArea.Size - 1 || y >= mapArea.Size - 1) continue;
                    if (mapArea.Tiles[x][y].GroundType != (int)GetId("GroundtypeWater")) continue;

                    if (
                            mapArea.Tiles[x - 1][y].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x - 1][y].GroundType != (int)GetId("GroundtypeClay") &&
                            mapArea.Tiles[x - 1][y - 1].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x - 1][y - 1].GroundType != GetId("GroundtypeClay") &&
                            mapArea.Tiles[x][y - 1].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x][y - 1].GroundType != (int)GetId("Gr(int)oundtypeClay") &&
                            mapArea.Tiles[x + 1][y - 1].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x + 1][y - 1].GroundType != (int)GetId("GroundtypeClay") &&
                            mapArea.Tiles[x + 1][y].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x + 1][y].GroundType != (int)GetId("GroundtypeClay") &&
                            mapArea.Tiles[x + 1][y + 1].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x + 1][y + 1].GroundType != (int)GetId("GroundtypeClay") &&
                            mapArea.Tiles[x][y + 1].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x][y + 1].GroundType != (int)GetId("GroundtypeClay") &&
                            mapArea.Tiles[x - 1][y + 1].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x - 1][y + 1].GroundType != (int)GetId("GroundtypeClay")
                            )
                        continue;

                    mapArea.Tiles[x][y].GroundType = (int)GetId("GroundtypeClay");
                }
            }
        }
    }
}

void F_DefaultMapGenerator::GenerateRock(F_MapArea& mapArea)
{
    for (auto i = 0; i < 10; i++)
    {
        auto x_center = rand() % mapArea.Size;
        auto y_center = rand() % mapArea.Size;
        auto r = 5 + rand() % 13;

        for (auto y = y_center - r; y <= y_center + r; y++)
        {
            for (auto x = x_center - r; x <= x_center + r; x++)
            {
                auto dx = x - x_center;
                auto dy = y - y_center;

                if (dx * dx + dy * dy >= r * r) continue;
                if (x < 0 || y < 0 || x >= mapArea.Size || y >= mapArea.Size) continue;
                if (mapArea.Tiles[x][y].Elevation < 4) continue;

                mapArea.Tiles[x][y].GroundType = (int)GetId("GroundtypeRock");
            }
        }
    }
}

void F_DefaultMapGenerator::GenerateTrees(F_MapArea& mapArea)
{
    for (auto i = 0; i < 30; i++)
    {
        auto x = rand() % mapArea.Size;
        auto y = rand() % mapArea.Size;
        auto num_trees = 15 + rand() % 15;

        for (auto j = 0; j < num_trees; j++)
        {
            if (x >= 0 && y >= 0 && x < mapArea.Size && y < mapArea.Size)
            {
                if (DistToPlayerStartingPos(mapArea, x, y) < PlayerStartingAreaSize) continue;

                if (mapArea.Tiles[x][y].GroundType == (int)GetId("GroundtypeGrass"))
                    if (mapArea.Tiles[x][y].Objects.size() == 0)
                        mapArea.Tiles[x][y].Objects.push_back(MakeUPtr<F_Object>("ObjectTree1"));
            }

            x += rand() % 7 - rand() % 7;
            y += rand() % 7 - rand() % 7;
        }
    }
    for (auto i = 0; i < 30; i++)
    {
        auto x = rand() % mapArea.Size;
        auto y = rand() % mapArea.Size;
        auto num_trees = 15 + rand() % 15;

        for (auto j = 0; j < num_trees; j++)
        {
            if (x >= 0 && y >= 0 && x < mapArea.Size && y < mapArea.Size)
            {
                if (DistToPlayerStartingPos(mapArea, x, y) < PlayerStartingAreaSize) continue;

                if (mapArea.Tiles[x][y].GroundType == (int)GetId("GroundtypeGrass"))
                    if (mapArea.Tiles[x][y].Objects.size() == 0)
                        mapArea.Tiles[x][y].Objects.push_back(MakeUPtr<F_Object>("ObjectTree2"));
            }

            x += rand() % 7 - rand() % 7;
            y += rand() % 7 - rand() % 7;
        }
    }
}

void F_DefaultMapGenerator::GenerateBushes(F_MapArea& mapArea)
{
    for (auto i = 0; i < 200; i++)
    {
        auto x = rand() % mapArea.Size;
        auto y = rand() % mapArea.Size;

        if (DistToPlayerStartingPos(mapArea, x, y) < PlayerStartingAreaSize) continue;

        if (mapArea.Tiles[x][y].GroundType == (int)GetId("GroundtypeGrass"))
            if (mapArea.Tiles[x][y].Objects.size() == 0)
                mapArea.Tiles[x][y].Objects.push_back(MakeUPtr<F_Object>("ObjectBush1"));
    }
}

void F_DefaultMapGenerator::GenerateSmallStones(F_MapArea& mapArea)
{
    for (auto i = 0; i < 200; i++)
    {
        auto x = rand() % mapArea.Size;
        auto y = rand() % mapArea.Size;

        if (DistToPlayerStartingPos(mapArea, x, y) < PlayerStartingAreaSize) continue;

        if (mapArea.Tiles[x][y].GroundType != (int)GetId("GroundtypeWater"))
            if (mapArea.Tiles[x][y].Objects.size() == 0)
                mapArea.Tiles[x][y].Objects.push_back(MakeUPtr<F_Object>("ObjectSmallStone"));
    }
}

//void F_DefaultMapGenerator::GenerateTallGrass(F_MapArea& mapArea)
//{
//    for (auto i = 0; i < 7000; i++)
//    {
//        auto x = rand() % mapArea.Size;
//        auto y = rand() % mapArea.Size;

//        if (DistToPlayerStartingPos(mapArea, x, y) < PlayerStartingAreaSize) continue;

//        if (mapArea.Tiles[x][y].GroundType == (int)GetId("GroundtypeGrass"))
//            if (mapArea.Tiles[x][y].Objects.size() == 0)
//                mapArea.Tiles[x][y].Objects.push_back(MakeUPtr<F_Object>("ObjectTallGrass"));
//    }
//}

void F_DefaultMapGenerator::GeneratePinkFlowers(F_MapArea& mapArea)
{
    for (auto i = 0; i < 100; i++)
    {
        auto x = rand() % mapArea.Size;
        auto y = rand() % mapArea.Size;

        if (mapArea.Tiles[x][y].GroundType == (int)GetId("GroundtypeGrass"))
            if (mapArea.Tiles[x][y].Objects.size() == 0)
                mapArea.Tiles[x][y].Objects.push_back(MakeUPtr<F_Object>("ObjectPinkFlower"));
    }
}

int F_DefaultMapGenerator::DistToPlayerStartingPos(F_MapArea& mapArea, int mapX, int mapY)
{
    auto dx = mapArea.PlayerStartPosition.X - mapX;
    auto dy = mapArea.PlayerStartPosition.Y - mapY;
    auto distance = std::sqrt(dx * dx + dy * dy);

    return distance;
}

void F_DefaultMapGenerator::GenerateMobs(F_MapArea& mapArea)
{
    for (auto i = 0; i < 200; i++)
    {
        auto x = rand() % mapArea.Size;
        auto y = rand() % mapArea.Size;

        if (DistToPlayerStartingPos(mapArea, x, y) < PlayerStartingAreaSize) continue;

        if (mapArea.Tiles[x][y].GroundType != (int)GetId("GroundtypeWater") && mapArea.Tiles[x][y].mob == nullptr)
        {
            mapArea.Tiles[x][y].mob = std::make_unique<F_Mob>(x, y);
            mapArea.MobsMirror.push_back(std::ref(mapArea.Tiles[x][y].mob));
        }
    }
}

void F_DefaultMapGenerator::GenerateQuestCaves(F_Engine& engine, F_MapArea& mapArea, UPtr<F_WorldMap>& worldMap)
{
    auto warp_from_map_id = worldMap->MapAreas.size() - 1;

    F_QuestCaveMapGenerator questCaveMapGenerator;

    for (auto i = 0; i < 20; i++)
    {
        auto x = rand() % 94 + 3;
        auto y = rand() % 94 + 3;

        if (DistToPlayerStartingPos(mapArea, x, y) < PlayerStartingAreaSize) continue;

        if (mapArea.Tiles[x][y].GroundType != (int)GetId("GroundtypeWater"))
        {
            mapArea.Tiles[x][y].Objects.push_back(MakeUPtr<F_Object>("ObjectQuestCaveEntrance"));
            mapArea.Tiles[x][y].WarpToMap = worldMap->MapAreas.size();

            worldMap->MapAreas.push_back(std::make_unique<F_MapArea>(engine, worldMap->MapAreaSize));

            auto& quest_cave_map_area = worldMap->MapAreas.at(worldMap->MapAreas.size() - 1);

            questCaveMapGenerator.GenerateQuestCaveMapArea(*quest_cave_map_area, { x, y }, warp_from_map_id);
        }
    }
}

}
