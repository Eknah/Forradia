// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "ValleyMapGenerator.h"
#include "../engine/PlanetWorldMap.h"
#include "framework/worldStructure/Object.h"
#include "QuestCaveMapGenerator.h"

namespace Forradia
{

    void
        ValleyMapGenerator::GenerateMapArea(Point3 worldPos) const
    {
        worldMap->areas[worldPos.x][worldPos.y][worldPos.z] =  MakeUPtr<MapArea>(e, worldMap->mapAreaSize, worldPos);

        auto mapArea = worldMap->GetArea(worldPos).get();

        ClearToGrass(mapArea);
        GeneratePlayerStartingPosition(mapArea);
        GenerateElevation(mapArea);
        GenerateRock(mapArea);
        GenerateRivers(mapArea);
        GenerateTrees(mapArea);
        GenerateBushes(mapArea);
        GenerateSmallStones(mapArea);
        GeneratePinkFlowers(mapArea);
        GenerateTallGrass(mapArea);
        GenerateVillage(mapArea);
        GenerateMobs(mapArea);
        GenerateQuestCaves(e, mapArea, worldMap);
    }

    void ValleyMapGenerator::ClearToGrass(MapArea* mapArea) const
    {
        for (auto tileY = 0; tileY < mapArea->size; tileY++)
            for (auto tileX = 0; tileX < mapArea->size; tileX++)

                mapArea->tiles[tileX][tileY].groundType = GetId("GroundTypeGrass");
    }

    void ValleyMapGenerator::GeneratePlayerStartingPosition(MapArea* mapArea) const
    {
        mapArea->spawnPos = { CFloat(mapArea->size / 2), CFloat(mapArea->size / 2) };
    }

    void ValleyMapGenerator::GenerateElevation(MapArea* mapArea) const
    {
        for (auto y = 0; y < mapArea->size; y++)
        {
            for (auto x = 0; x < mapArea->size; x++)
            {
                auto dxLeft = x;
                auto dxRight = mapArea->size - x;
                auto dyTop = y;
                auto dyBottom = mapArea->size - y;

                auto elevHorizontal = std::max(dxLeft, dxRight);
                auto elevVertical = std::max(dyTop, dyBottom);
                auto elev = std::max(std::max(elevHorizontal, elevVertical), 86) * 5 - 40;

                mapArea->tiles[x][y].elevation = elev / 1.5f;

            }
        }

        for (auto i = 0; i < 60; i++)
        {
            auto centerTileX = 0;
            auto centerTileY = 0;
            auto maxr = 4 + rnd.Next() % 6;

            do
            {
                centerTileX = rnd.Next() % mapArea->size;
                centerTileY = rnd.Next() % mapArea->size;
                maxr = 1 + rnd.Next() % 6;
            } while (std::abs(centerTileX - mapArea->size / 2) < villageSize / 2
                || std::abs(centerTileY - mapArea->size / 2) < villageSize / 2);

            for (auto r = maxr; r >= 0; r--)
            {
                for (auto y = centerTileY - r; y <= centerTileY + r; y++)
                {
                    for (auto x = centerTileX - r; x <= centerTileX + r; x++)
                    {
                        auto dx = x - centerTileX;
                        auto dy = y - centerTileY;

                        if (dx * dx + dy * dy >= r * r) continue;
                        if (x < 0 || y < 0 || x >= mapArea->size || y >= mapArea->size) continue;

                        mapArea->tiles[x][y].elevation += 5;
                    }
                }
            }
        }

    }

    void ValleyMapGenerator::GenerateRock(MapArea* mapArea) const
    {
        for (auto i = 0; i < 30; i++)
        {

            auto centerx = 0;
            auto centery = 0;
            auto r = 0;

            do
            {

                centerx = rnd.Next() % mapArea->size;
                centery = rnd.Next() % mapArea->size;
                r = 5 + rnd.Next() % 13;

            } while (std::abs(centerx - mapArea->size / 2) < villageSize / 2 + r  || std::abs(centery - mapArea->size / 2) < villageSize / 2 + r);


            for (auto y = centery - r; y <= centery + r; y++)
            {
                for (auto x = centerx - r; x <= centerx + r; x++)
                {
                    auto dx = x - centerx;
                    auto dy = y - centery;

                    if (dx * dx + dy * dy >= r * r) continue;
                    if (x < 0 || y < 0 || x >= mapArea->size || y >= mapArea->size) continue;
                    if (mapArea->tiles[x][y].elevation < 150) continue;

                    mapArea->tiles[x][y].groundType = GetId("GroundTypeRock");
                }
            }
        }
    }

    void ValleyMapGenerator::GenerateRivers(MapArea* mapArea) const
    {
        for (auto i = 0; i < 6; i++)
        {
            float xstart = rnd.Next() % mapArea->size;
            float ystart = rnd.Next() % mapArea->size;

            float xdest = mapArea->size / 2;
            float ydest = mapArea->size / 2;

            auto dx = xdest - xstart;
            auto dy = ydest - ystart;

            auto numSteps = std::max(std::abs(dx), std::abs(dy));
            auto xstep = dx / numSteps;
            auto ystep = dy / numSteps;

            auto angleStart = std::atan2(dy, dx);

            for (auto j = 0.0f; j < numSteps; j += 0.1f)
            {
                auto x = xstart + j * xstep;
                auto y = ystart + j * ystep;

                auto angle = angleStart + std::cos(j * M_PI / 10.0f);

                x += std::cos(angle) * 4.0f;
                y += std::sin(angle) * 4.0f;

                auto xi = CInt(x);
                auto yi = CInt(y);

                if (xi >= 0 && yi >= 0 && xi < mapArea->size && yi < mapArea->size)
                    mapArea->tiles[xi][yi].groundType = GetId("GroundTypeWater");
            }
        }
    }

    void ValleyMapGenerator::GenerateTrees(MapArea* mapArea) const
    {
        for (auto i = 0; i < 30; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;
            auto numTrees = 15 + rnd.Next() % 15;

            for (auto j = 0; j < numTrees; j++)
            {
                if (x >= 0 && y >= 0 && x < mapArea->size && y < mapArea->size)
                {
                    if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

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
                if (x >= 0 && y >= 0 && x < mapArea->size && y < mapArea->size)
                {
                    if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

                    if (mapArea->tiles[x][y].groundType == GetId("GroundTypeGrass"))
                        if (mapArea->tiles[x][y].objects.size() == 0)
                            mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectTree2"));
                }

                x += rnd.Next() % 7 - rnd.Next() % 7;
                y += rnd.Next() % 7 - rnd.Next() % 7;
            }
        }
    }

    void ValleyMapGenerator::GenerateVillage(MapArea* mapArea) const
    {

        auto xcenter = mapArea->size / 2;
        auto ycenter = mapArea->size / 2;
        auto xstart = xcenter - villageSize / 2;
        auto ystart = xcenter - villageSize / 2;
        auto xend = xstart + villageSize;
        auto yend = ystart + villageSize;

        for (auto y = ystart; y <= yend; y++)
        {
            for (auto x = xstart; x <= xend; x++)
            {
                mapArea->tiles[x][y].groundType = GetId("GroundTypeGrass");
                mapArea->tiles[x][y].objects.clear();
            }
        }

        for (auto y = ycenter - 1; y <= ycenter + 1; y++)
        {
            for (auto x = xcenter - 1; x <= xcenter + 1; x++)
            {
                mapArea->tiles[x][y].groundType = GetId("GroundTypeCobblestone");
            }
        }

        for (auto y = 0; y < mapArea->size; y++)
        {
            mapArea->tiles[xcenter][y].objects.clear();
            mapArea->tiles[xcenter][y].groundType = GetId("GroundTypeTrail");
        }

        for (auto x = 0; x < mapArea->size; x++)
        {
            mapArea->tiles[x][ycenter].objects.clear();
            mapArea->tiles[x][ycenter].groundType = GetId("GroundTypeTrail");
        }

        for (auto y = ystart; y <= yend; y++)
            mapArea->tiles[xcenter][y].groundType = GetId("GroundTypeCobblestone");

        for (auto x = xstart; x <= xend; x++)
            mapArea->tiles[x][ycenter].groundType = GetId("GroundTypeCobblestone");

        for (auto y = ystart; y <= yend; y++)
        {
            if (y == ycenter) continue;

            mapArea->tiles[xstart + 1][y].objects.push_back(MakeSPtr<Object>("ObjectBush1"));
            mapArea->tiles[xend - 1][y].objects.push_back(MakeSPtr<Object>("ObjectBush1"));
            mapArea->tiles[xstart][y].objects.push_back(MakeSPtr<Object>("ObjectWoodFence", false, false, 180));
            mapArea->tiles[xend][y].objects.push_back(MakeSPtr<Object>("ObjectWoodFence", false, false, 0));
        }

        for (auto x = xstart; x <= xend; x++)
        {
            if (x == xcenter) continue;

            mapArea->tiles[x][ystart + 1].objects.push_back(MakeSPtr<Object>("ObjectBush1"));
            mapArea->tiles[x][yend - 1].objects.push_back(MakeSPtr<Object>("ObjectBush1"));
            mapArea->tiles[x][ystart].objects.push_back(MakeSPtr<Object>("ObjectWoodFence", false, false, 90));
            mapArea->tiles[x][yend].objects.push_back(MakeSPtr<Object>("ObjectWoodFence", false, false, 270));
        }

        auto houseWidth = 4;
        auto houseDepth = 3;

        auto housexcenter = xcenter + 5;
        auto houseycenter = ycenter + 5;
        auto housexstart = housexcenter - houseWidth / 2;
        auto houseystart = houseycenter - houseDepth / 2;
        auto housexend = housexstart + houseWidth;
        auto houseyend = houseystart + houseDepth;

        for (auto y = houseystart - 1; y <= houseyend + 1; y++)
        {
            for (auto x = housexstart - 1; x <= housexend + 1; x++)
            {
                mapArea->tiles[x][y].elevation = mapArea->tiles[housexcenter][houseycenter].elevation;
            }
        }

        for (auto y = houseystart; y <= houseyend; y++)
        {
            for (auto x = housexstart; x <= housexend; x++)
            {
                mapArea->tiles[x][y].roof = MakeSPtr<Object>("ObjectRoof", false, false);
                mapArea->tiles[x][y].groundType = GetId("GroundTypeWoodfloor");
            }
        }

        for (auto y = houseystart; y <= houseyend; y++)
        {

            mapArea->tiles[housexstart][y].objects.push_back(MakeSPtr<Object>("ObjectWoodWall", false, false, 180));
            mapArea->tiles[housexend][y].objects.push_back(MakeSPtr<Object>("ObjectWoodWall", false, false, 0));
        }

        for (auto x = housexstart; x <= housexend; x++)
        {
            if (x != housexcenter)
                mapArea->tiles[x][houseystart].objects.push_back(
                    MakeSPtr<Object>("ObjectWoodWall", false, false, 90));

            mapArea->tiles[x][houseyend].objects.push_back(
                MakeSPtr<Object>("ObjectWoodWall", false, false, 270));
        }

        for (auto y = houseystart - 1; y != ycenter; y--)
        {
            mapArea->tiles[housexcenter][y].groundType = GetId("GroundTypeCobblestone");
        }

        auto anvilx = xcenter - 5;
        auto anvily = ycenter - 5;

        for (auto y = anvily - 2; y <= anvily + 2; y++)
        {
            for (auto x = anvilx - 2; x <= anvilx + 2; x++)
            {
                mapArea->tiles[x][y].groundType = GetId("GroundTypeCobblestone");
            }
        }

        mapArea->tiles[anvilx][anvily].objects.push_back(MakeSPtr<Object>("ObjectLargeAnvil", false));

        mapArea->tiles[xcenter + 1][ycenter - villageSize / 2].objects.push_back(MakeSPtr<Object>("ObjectStreetLantern", false));
        mapArea->tiles[xcenter + 1][ycenter + villageSize / 2].objects.push_back(MakeSPtr<Object>("ObjectStreetLantern", false));
        mapArea->tiles[xcenter + villageSize / 2][ycenter + 1].objects.push_back(MakeSPtr<Object>("ObjectStreetLantern", false));
        mapArea->tiles[xcenter - villageSize / 2][ycenter + 1].objects.push_back(MakeSPtr<Object>("ObjectStreetLantern", false));

    }

    int ValleyMapGenerator::DistToPlayerStartingPos(MapArea* mapArea, int tileX, int tileY) const
    {
        auto dx = mapArea->spawnPos.x - tileX;
        auto dy = mapArea->spawnPos.y - tileY;
        auto distance = std::sqrt(dx * dx + dy * dy);

        return CInt(distance);
    }


    void ValleyMapGenerator::GenerateBushes(MapArea* mapArea) const
    {
        for (auto i = 0; i < 200; i++)
        {
            auto tileX = rnd.Next() % mapArea->size;
            auto tileY = rnd.Next() % mapArea->size;

            if (DistToPlayerStartingPos(mapArea, tileX, tileY) < playerStartAreaSize) continue;

            if (mapArea->tiles[tileX][tileY].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[tileX][tileY].objects.size() == 0)
                    mapArea->tiles[tileX][tileY].objects.push_back(MakeSPtr<Object>("ObjectBush1"));
        }
    }

    void ValleyMapGenerator::GenerateSmallStones(MapArea* mapArea) const
    {
        for (auto i = 0; i < 200; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;

            if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

            if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater"))
                if (mapArea->tiles[x][y].objects.size() == 0)
                    mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectSmallStone"));
        }
    }

    void ValleyMapGenerator::GeneratePinkFlowers(MapArea* mapArea) const
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

    void ValleyMapGenerator::GenerateTallGrass(MapArea* mapArea) const
    {
        for (auto i = 0; i < 6000; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;

            if (mapArea->tiles[x][y].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[x][y].objects.size() == 0)
                    mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectTallGrass"));
        }
    }


    void ValleyMapGenerator::GenerateMobs(MapArea* mapArea) const
    {
        for (auto i = 0; i < 100; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;

            if (x == CInt(mapArea->spawnPos.x) && y == CInt(mapArea->spawnPos.y)) continue;
            if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

            if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater") && mapArea->tiles[x][y].actor == nullptr)
            {
                mapArea->tiles[x][y].actor = MakeUPtr<Mob>(e, CFloat(x), CFloat(y), "MobRabbit");
                mapArea->mobActorsMirror.insert({ mapArea->tiles[x][y].actor->actorId, std::ref(mapArea->tiles[x][y].actor) });
            }
        }

        for (auto i = 0; i < 100; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;

            if (x == CInt(mapArea->spawnPos.x) && y == CInt(mapArea->spawnPos.y)) continue;
            if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

            if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater") &&  mapArea->tiles[x][y].actor == nullptr)
            {
                mapArea->tiles[x][y].actor =  MakeUPtr<Mob>(e, CFloat(x), CFloat(y), "MobRat");
                mapArea->mobActorsMirror.insert({ mapArea->tiles[x][y].actor->actorId, std::ref(mapArea->tiles[x][y].actor) });
            }
        }

        for (auto i = 0; i < 100; i++)
        {
            auto x = rnd.Next() % mapArea->size;
            auto y = rnd.Next() % mapArea->size;

            if (x == CInt(mapArea->spawnPos.x) && y == CInt(mapArea->spawnPos.y)) continue;
            if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

            if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater") && mapArea->tiles[x][y].actor == nullptr)
            {
                mapArea->tiles[x][y].actor = MakeUPtr<Mob>(e, CFloat(x), CFloat(y), "MobPinkSlime");
                mapArea->mobActorsMirror.insert({ mapArea->tiles[x][y].actor->actorId, std::ref(mapArea->tiles[x][y].actor) });
            }
        }
    }

    void ValleyMapGenerator::GenerateQuestCaves(const IEngine& e, MapArea* mapArea, const UPtr<PlanetWorldMap>& worldMap) const
    {
        QuestCaveMapGenerator questCaveMapGenerator;

        for (auto floor = -1; floor >= -20; floor--)
        {
            auto x = rnd.Next() % 94 + 3;
            auto y = rnd.Next() % 94 + 3;

            if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

            auto xcenter = mapArea->size / 2;
            auto ycenter = mapArea->size / 2;
            auto xstartvillage = xcenter - villageSize / 2;
            auto ystartvillage = xcenter - villageSize / 2;
            auto xendvillage = xstartvillage + villageSize;
            auto yendvillage = ystartvillage + villageSize;

            if (x >= xstartvillage && y >= ystartvillage && x <= xendvillage && y <= yendvillage) continue;

            if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater"))
            {
                mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectQuestCaveEntrance"));
                mapArea->tiles[x][y].properties["WarpToFloor"] = std::to_string(floor);

                worldMap->areas[mapArea->worldCoord.x][mapArea->worldCoord.y][floor] = MakeUPtr<MapArea>(e, worldMap->mapAreaSize, Point3 { mapArea->worldCoord.x, mapArea->worldCoord.y, floor });

                auto& questCaveMapArea =  worldMap->areas[mapArea->worldCoord.x][mapArea->worldCoord.y][floor];

                questCaveMapGenerator.GenerateQuestCaveMapArea(questCaveMapArea.get(), { x, y });
            }
        }
    }

}  // namespace Forradia
