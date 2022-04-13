// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "DefaultMapGenerator.h"
#include "QuestCaveMapGenerator.h"
#include "../engine/PlanetWorldMap.h"
#include "framework/worldStructure/Object.h"
#include "../engine/Aliases.h"

namespace Forradia
{

    void DefaultMapGenerator::GenerateMapArea(Point3 worldPos) const
    {
        worldMap->areas[worldPos.x][worldPos.y][worldPos.z] =
            MakeUPtr<MapArea>(e, worldMap->mapAreaSize, worldPos);

        auto mapArea = worldMap->GetArea(worldPos).get();

        ClearToGrass(mapArea);
        GeneratePlayerStartingPosition(mapArea);
        GenerateElevation(mapArea);
        GenerateWater(mapArea);
        GenerateSand(mapArea);
        GenerateClay(mapArea);
        GenerateRock(mapArea);
        GenerateTrees(mapArea);
        GenerateBushes(mapArea);
        GenerateSmallStones(mapArea);
        GeneratePinkFlowers(mapArea);
        GenerateTallGrass(mapArea);
        GenerateMobs(mapArea);
        GenerateQuestCaves(e, mapArea, worldMap);
    }

    void DefaultMapGenerator::ClearToGrass(MapArea* mapArea) const
    {
        for (auto y = 0; y < mapArea->size; y++)
            for (auto x = 0; x < mapArea->size; x++)
                mapArea->tiles[x][y].groundType = GetId("GroundTypeGrass");
    }

    void DefaultMapGenerator::GeneratePlayerStartingPosition(MapArea* mapArea) const
    {
        mapArea->spawnPos.x = CFloat(rnd.Next() % mapArea->size);
        mapArea->spawnPos.y = CFloat(rnd.Next() % mapArea->size);
    }

    void DefaultMapGenerator::GenerateElevation(MapArea* mapArea) const
    {
        for (auto i = 0; i < 40; i++)
        {
            auto centerx = rnd.Next() % mapArea->size;
            auto centery = rnd.Next() % mapArea->size;
            auto maxr = 4 + rnd.Next() % 12;

            for (auto r = maxr; r >= 0; r -= 1)
            {
                for (auto y = centery - r; y <= centery + r; y++)
                {
                    for (auto x = centerx - r; x <= centerx + r; x++)
                    {
                        auto dx = x - centerx;
                        auto dy = y - centery;

                        if (x < 0 || y < 0 || x >= mapArea->size || y >= mapArea->size) continue;

                        mapArea->tiles[x][y].elevation += 2;
                    }
                }
            }
        }
    }

    void DefaultMapGenerator::GenerateWater(MapArea* mapArea) const
    {
        for (auto i = 0; i < 20; i++)
        {
            auto centerx = rnd.Next() % mapArea->size;
            auto centery = rnd.Next() % mapArea->size;
            auto r = 5 + rnd.Next() % 13;

            for (auto y = centery - r; y <= centery + r; y++)
            {
                for (auto x = centerx - r; x <= centerx + r; x++)
                {
                    auto dx = x - centerx;
                    auto dy = y - centery;

                    if (dx * dx + dy * dy >= r * r) continue;
                    if (x <= 0 || y <= 0 || x >= mapArea->size - 1 || y >= mapArea->size - 1) continue;
                    if (mapArea->tiles[x][y].elevation > 0) continue;
                    if (mapArea->tiles[x - 1][y].elevation > 0) continue;
                    if (mapArea->tiles[x - 1][y - 1].elevation > 0) continue;
                    if (mapArea->tiles[x][y - 1].elevation > 0) continue;
                    if (mapArea->tiles[x + 1][y].elevation > 0) continue;
                    if (mapArea->tiles[x + 1][y + 1].elevation > 0) continue;
                    if (mapArea->tiles[x][y + 1].elevation > 0) continue;
                    if (mapArea->tiles[x - 1][y + 1].elevation > 0) continue;
                    if (mapArea->tiles[x + 1][y - 1].elevation > 0) continue;
                    if (DistToPlayerStartingPos(mapArea, x, y) < playerStartingAreaSize) continue;

                    mapArea->tiles[x][y].groundType = GetId("GroundTypeWater");
                }
            }
        }
    }

    void DefaultMapGenerator::GenerateSand(MapArea* mapArea) const
    {
        for (auto i = 0; i < 30; i++)
        {
            auto centerx = rnd.Next() % mapArea->size;
            auto centery = rnd.Next() % mapArea->size;
            auto r = 4 + rnd.Next() % 5;

            for (auto j = 0; j < r; j++)
            {
                for (auto y = centery - r; y <= centery + r; y++)
                {
                    for (auto x = centerx - r; x <= centerx + r; x++)
                    {
                        auto dx = x - centerx;
                        auto dy = y - centery;

                        if (dx * dx + dy * dy >= r * r) continue;
                        if (x <= 0 || y <= 0 || x >= mapArea->size - 1 || y >= mapArea->size - 1) continue;
                        if (mapArea->tiles[x][y].groundType ==  GetId("GroundTypeWater")) continue;
                        if (mapArea->tiles[x][y].elevation > 5) continue;

                        if (mapArea->tiles[x - 1][y].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x - 1][y].groundType !=
                            GetId("GroundTypeSand") &&
                            mapArea->tiles[x - 1][y - 1].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x - 1][y - 1].groundType !=
                            GetId("GroundTypeSand") &&
                            mapArea->tiles[x][y - 1].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x][y - 1].groundType !=
                            GetId("GroundTypeSand") &&
                            mapArea->tiles[x + 1][y - 1].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x + 1][y - 1].groundType !=
                            GetId("GroundTypeSand") &&
                            mapArea->tiles[x + 1][y].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x + 1][y].groundType !=
                            GetId("GroundTypeSand") &&
                            mapArea->tiles[x + 1][y + 1].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x + 1][y + 1].groundType !=
                            GetId("GroundTypeSand") &&
                            mapArea->tiles[x][y + 1].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x][y + 1].groundType !=
                            GetId("GroundTypeSand") &&
                            mapArea->tiles[x - 1][y + 1].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x - 1][y + 1].groundType !=
                            GetId("GroundTypeSand"))
                            continue;

                        mapArea->tiles[x][y].groundType = GetId("GroundTypeSand");
                    }
                }
            }
        }
    }

    void DefaultMapGenerator::GenerateClay(MapArea* mapArea) const
    {
        for (auto i = 0; i < 30; i++)
        {
            auto centerx = rnd.Next() % mapArea->size;
            auto centery = rnd.Next() % mapArea->size;
            auto r = 2 + rnd.Next() % 3;

            for (auto j = 0; j < r; j++)
            {
                for (auto y = centery - r; y <= centery + r; y++)
                {
                    for (auto x = centerx - r; x <= centerx + r; x++)
                    {
                        auto dx = x - centerx;
                        auto dy = y - centery;

                        if (dx * dx + dy * dy >= r * r) continue;
                        if (x <= 0 || y <= 0 || x >= mapArea->size - 1 || y >= mapArea->size - 1) continue;
                        if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater")) continue;

                        if (mapArea->tiles[x - 1][y].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x - 1][y].groundType !=
                            GetId("GroundTypeClay") &&
                            mapArea->tiles[x - 1][y - 1].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x - 1][y - 1].groundType !=
                            GetId("GroundTypeClay") &&
                            mapArea->tiles[x][y - 1].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x][y - 1].groundType !=
                            GetId("GroundTypeClay") &&
                            mapArea->tiles[x + 1][y - 1].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x + 1][y - 1].groundType !=
                            GetId("GroundTypeClay") &&
                            mapArea->tiles[x + 1][y].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x + 1][y].groundType !=
                            GetId("GroundTypeClay") &&
                            mapArea->tiles[x + 1][y + 1].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x + 1][y + 1].groundType !=
                            GetId("GroundTypeClay") &&
                            mapArea->tiles[x][y + 1].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x][y + 1].groundType !=
                            GetId("GroundTypeClay") &&
                            mapArea->tiles[x - 1][y + 1].groundType !=
                            GetId("GroundTypeWater") &&
                            mapArea->tiles[x - 1][y + 1].groundType !=
                            GetId("GroundTypeClay"))
                            continue;

                        mapArea->tiles[x][y].groundType = GetId("GroundTypeClay");
                    }
                }
            }
        }
    }

    void DefaultMapGenerator::GenerateRock(MapArea* mapArea) const
    {
        for (auto i = 0; i < 10; i++)
        {
            auto centerx = rnd.Next() % mapArea->size;
            auto centery = rnd.Next() % mapArea->size;
            auto r = 5 + rnd.Next() % 13;

            for (auto y = centery - r; y <= centery + r; y++)
            {
                for (auto x = centerx - r; x <= centerx + r; x++)
                {
                    auto dx = x - centerx;
                    auto dy = y - centery;

                    if (dx * dx + dy * dy >= r * r) continue;
                    if (x < 0 || y < 0 || x >= mapArea->size || y >= mapArea->size) continue;
                    if (mapArea->tiles[x][y].elevation < 4) continue;

                    mapArea->tiles[x][y].groundType = GetId("GroundTypeRock");
                }
            }
        }
    }

    void DefaultMapGenerator::GenerateTrees(MapArea* mapArea) const
    {
        for (auto i = 0; i < 30; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;
            auto numTrees = 15 + rnd.Next() % 15;

            for (auto j = 0; j < numTrees; j++)
            {
                if (x >= 0 && y >= 0 && x < mapArea->size &&
                    y < mapArea->size)
                {
                    if (DistToPlayerStartingPos(mapArea, x, y) < playerStartingAreaSize) continue;

                    if (mapArea->tiles[x][y].groundType == GetId("GroundTypeGrass"))
                        if (mapArea->tiles[x][y].objects.size() == 0)
                            mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectTree1"));
                }

                x += rnd.Next() % 7 - rnd.Next() % 7;
                y += rnd.Next() % 7 - rnd.Next() % 7;
            }
        }
        for (auto i = 0; i < 30; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;
            auto numTrees = 15 + rnd.Next() % 15;

            for (auto j = 0; j < numTrees; j++)
            {
                if (x >= 0 && y >= 0 && x < mapArea->size &&
                    y < mapArea->size)
                {
                    if (DistToPlayerStartingPos(mapArea, x, y) < playerStartingAreaSize) continue;

                    if (mapArea->tiles[x][y].groundType == GetId("GroundTypeGrass"))
                        if (mapArea->tiles[x][y].objects.size() == 0)
                            mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectTree2"));
                }

                x += rnd.Next() % 7 - rnd.Next() % 7;
                y += rnd.Next() % 7 - rnd.Next() % 7;
            }
        }
    }

    void DefaultMapGenerator::GenerateBushes(MapArea* mapArea) const
    {
        for (auto i = 0; i < 200; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;

            if (DistToPlayerStartingPos(mapArea, x, y) < playerStartingAreaSize) continue;

            if (mapArea->tiles[x][y].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[x][y].objects.size() == 0)
                    mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectBush1"));
        }
    }

    void DefaultMapGenerator::GenerateSmallStones(MapArea* mapArea) const
    {
        for (auto i = 0; i < 200; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;

            if (DistToPlayerStartingPos(mapArea, x, y) < playerStartingAreaSize) continue;

            if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater"))
                if (mapArea->tiles[x][y].objects.size() == 0)
                    mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectSmallStone"));
        }
    }

    void DefaultMapGenerator::GeneratePinkFlowers(MapArea* mapArea) const
    {
        for (auto i = 0; i < 100; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;

            if (mapArea->tiles[x][y].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[x][y].objects.size() == 0)
                    mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectPinkFlower"));
        }
    }

    void DefaultMapGenerator::GenerateTallGrass(MapArea* mapArea) const
    {
        for (auto i = 0; i < 1000; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;

            if (mapArea->tiles[x][y].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[x][y].objects.size() == 0)
                    mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectTallGrass"));
        }
    }

    int DefaultMapGenerator::DistToPlayerStartingPos(MapArea* mapArea, int tileX, int tileY) const
    {
        auto dx = mapArea->spawnPos.x - tileX;
        auto dy = mapArea->spawnPos.y - tileY;
        auto distance = std::sqrt(dx * dx + dy * dy);

        return CInt(distance);
    }

    void DefaultMapGenerator::GenerateMobs(MapArea* mapArea) const
    {
        for (auto i = 0; i < 200; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;

            if (x == CInt(mapArea->spawnPos.x)  && y == CInt(mapArea->spawnPos.y)) continue;
            if (DistToPlayerStartingPos(mapArea, x, y) < playerStartingAreaSize) continue;

            if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater") && mapArea->tiles[x][y].actor == nullptr)
            {
                mapArea->tiles[x][y].actor = MakeUPtr<Mob>(e, CFloat(x), CFloat(y), "MobRabbit");
                mapArea->mobActorsMirror.insert({ mapArea->tiles[x][y].actor->actorId, std::ref(mapArea->tiles[x][y].actor) });
            }
        }

        for (auto i = 0; i < 200; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;

            if (x == CInt(mapArea->spawnPos.x) && y == CInt(mapArea->spawnPos.y)) continue;
            if (DistToPlayerStartingPos(mapArea, x, y) < playerStartingAreaSize) continue;

            if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater") && mapArea->tiles[x][y].actor == nullptr)
            {
                mapArea->tiles[x][y].actor = MakeUPtr<Mob>(e, CFloat(x), CFloat(y), "MobRat");
                mapArea->mobActorsMirror.insert({ mapArea->tiles[x][y].actor->actorId, std::ref(mapArea->tiles[x][y].actor) });
            }
        }
    }

    void DefaultMapGenerator::GenerateQuestCaves(const IEngine& e, MapArea* mapArea, const UPtr<PlanetWorldMap>& worldMap) const
    {
        QuestCaveMapGenerator questCaveMapGenerator;

        for (auto floor = -1; floor >= -20; floor--)
        {
            auto x = rnd.Next() % 94 + 3;
            auto y = rnd.Next() % 94 + 3;

            if (DistToPlayerStartingPos(mapArea, x, y) < playerStartingAreaSize) continue;

            if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater"))
            {
                mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectQuestCaveEntrance"));
                mapArea->tiles[x][y].properties["WarpToFloor"] = std::to_string(floor);

                worldMap->areas[mapArea->worldCoord.x][mapArea->worldCoord.y][floor] = MakeUPtr<MapArea>(e, worldMap->mapAreaSize, Point3 { mapArea->worldCoord.x, mapArea->worldCoord.y, floor });

                auto& questCaveMapArea = worldMap->areas[mapArea->worldCoord.x][mapArea->worldCoord.y][floor];

                questCaveMapGenerator.GenerateQuestCaveMapArea(questCaveMapArea.get(), { x, y });
            }
        }
    }

}  // namespace Forradia
