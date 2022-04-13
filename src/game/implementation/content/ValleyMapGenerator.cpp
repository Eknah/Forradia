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
        ValleyMapGenerator::GenerateMapArea(
            int worldX, int worldY, int worldZ) const
    {
        worldMap->areas[worldX][worldY][worldZ] =
            MakeUPtr<MapArea>(e, worldMap->mapAreaSize, worldX, worldY, worldZ);

        auto mapArea = worldMap->areas[worldX][worldY][worldZ].get();

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

    void
        ValleyMapGenerator::ClearToGrass(MapArea* mapArea) const
    {
        for (auto tileY = 0; tileY < mapArea->size; tileY++)
            for (auto tileX = 0; tileX < mapArea->size; tileX++)

                mapArea->tiles[tileX][tileY].groundType = GetId("GroundTypeGrass");
    }

    void
        ValleyMapGenerator::GeneratePlayerStartingPosition
        (MapArea* mapArea) const
    {
        mapArea->spawnPos = { static_cast<float>(mapArea->size / 2),
                             static_cast<float>(mapArea->size / 2) };
    }

    void
        ValleyMapGenerator::GenerateElevation(MapArea* mapArea) const
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
            auto maxR = 4 + random.Next() % 6;

            do
            {
                centerTileX = random.Next() % mapArea->size;
                centerTileY = random.Next() % mapArea->size;
                maxR = 1 + random.Next() % 6;
            } while (std::abs(centerTileX - mapArea->size / 2) < villageSize / 2
                || std::abs(centerTileY - mapArea->size / 2) < villageSize / 2);

            for (auto r = maxR; r >= 0; r--)
            {
                for (auto tileY = centerTileY - r; tileY <= centerTileY + r; tileY++)
                {
                    for (auto tileX = centerTileX - r; tileX <= centerTileX + r; tileX++)
                    {
                        auto dx = tileX - centerTileX;
                        auto dy = tileY - centerTileY;

                        if (dx * dx + dy * dy >= r * r)
                            continue;
                        if (tileX < 0 || tileY < 0 || tileX >= mapArea->size ||
                            tileY >= mapArea->size)
                            continue;

                        mapArea->tiles[tileX][tileY].elevation += 5;
                    }
                }
            }
        }



    }

    void
        ValleyMapGenerator::GenerateRock(MapArea* mapArea) const
    {
        for (auto i = 0; i < 30; i++)
        {

            auto centerTileX = 0;
            auto centerTileY = 0;
            auto r = 0;

            do
            {
                centerTileX = random.Next() % mapArea->size;
                centerTileY = random.Next() % mapArea->size;
                r = 5 + random.Next() % 13;
            } while (std::abs(centerTileX - mapArea->size / 2) < villageSize / 2 + r
                || std::abs(centerTileY - mapArea->size / 2) < villageSize / 2 + r);


            for (auto tileY = centerTileY - r; tileY <= centerTileY + r; tileY++)
            {
                for (auto tileX = centerTileX - r; tileX <= centerTileX + r; tileX++)
                {
                    auto dx = tileX - centerTileX;
                    auto dy = tileY - centerTileY;

                    if (dx * dx + dy * dy >= r * r)
                        continue;
                    if (tileX < 0 || tileY < 0 || tileX >= mapArea->size ||
                        tileY >= mapArea->size)
                        continue;
                    if (mapArea->tiles[tileX][tileY].elevation < 150)
                        continue;

                    mapArea->tiles[tileX][tileY].groundType = GetId("GroundTypeRock");
                }
            }
        }
    }

    void
        ValleyMapGenerator::GenerateRivers(MapArea* mapArea) const
    {
        for (auto i = 0; i < 6; i++)
        {
            float xstart = random.Next() % mapArea->size;
            float ystart = random.Next() % mapArea->size;

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

                auto xi = static_cast<int>(x);
                auto yi = static_cast<int>(y);

                if (xi >= 0 && yi >= 0 && xi < mapArea->size && yi < mapArea->size)
                    mapArea->tiles[xi][yi].groundType = GetId("GroundTypeWater");
            }
        }
    }

    void
        ValleyMapGenerator::GenerateTrees(MapArea* mapArea) const
    {
        for (auto i = 0; i < 30; i++)
        {
            auto tileX = random.Next() % mapArea->size;
            auto tileY = random.Next() % mapArea->size;
            auto numTrees = 15 + random.Next() % 15;

            for (auto j = 0; j < numTrees; j++)
            {
                if (tileX >= 0 && tileY >= 0 && tileX < mapArea->size &&
                    tileY < mapArea->size)
                {
                    if (DistToPlayerStartingPos(mapArea, tileX, tileY) <
                        playerStartingAreaSize)
                        continue;

                    if (mapArea->tiles[tileX][tileY].groundType ==
                        GetId("GroundTypeGrass"))
                        if (mapArea->tiles[tileX][tileY].objects.size() == 0)
                            mapArea->tiles[tileX][tileY].objects.push_back(
                                MakeSPtr<Object>("ObjectTree1"));
                }

                tileX += random.Next() % 7 - random.Next() % 7;
                tileY += random.Next() % 7 - random.Next() % 7;
            }
        }
        for (auto i = 0; i < 30; i++)
        {
            auto tileX = random.Next() % mapArea->size;
            auto tileY = random.Next() % mapArea->size;
            auto numTrees = 15 + random.Next() % 15;

            for (auto j = 0; j < numTrees; j++)
            {
                if (tileX >= 0 && tileY >= 0 && tileX < mapArea->size &&
                    tileY < mapArea->size)
                {
                    if (DistToPlayerStartingPos(mapArea, tileX, tileY) <
                        playerStartingAreaSize)
                        continue;

                    if (mapArea->tiles[tileX][tileY].groundType ==
                        GetId("GroundTypeGrass"))
                        if (mapArea->tiles[tileX][tileY].objects.size() == 0)
                            mapArea->tiles[tileX][tileY].objects.push_back(
                                MakeSPtr<Object>("ObjectTree2"));
                }

                tileX += random.Next() % 7 - random.Next() % 7;
                tileY += random.Next() % 7 - random.Next() % 7;
            }
        }
    }

    void
        ValleyMapGenerator::GenerateVillage(MapArea* mapArea) const
    {

        auto xCenter = mapArea->size / 2;
        auto yCenter = mapArea->size / 2;
        auto xStart = xCenter - villageSize / 2;
        auto yStart = xCenter - villageSize / 2;
        auto xEnd = xStart + villageSize;
        auto yEnd = yStart + villageSize;

        for (auto y = yStart; y <= yEnd; y++)
        {

            for (auto x = xStart; x <= xEnd; x++)
            {
                mapArea->tiles[x][y].groundType = GetId("GroundTypeGrass");
                mapArea->tiles[x][y].objects.clear();
            }
        }

        for (auto y = yCenter - 1; y <= yCenter + 1; y++)
        {

            for (auto x = xCenter - 1; x <= xCenter + 1; x++)
            {
                mapArea->tiles[x][y].groundType = GetId("GroundTypeCobblestone");
            }
        }

        for (auto y = 0; y < mapArea->size; y++)
        {
            mapArea->tiles[xCenter][y].objects.clear();
            mapArea->tiles[xCenter][y].groundType = GetId("GroundTypeTrail");
        }

        for (auto x = 0; x < mapArea->size; x++)
        {
            mapArea->tiles[x][yCenter].objects.clear();
            mapArea->tiles[x][yCenter].groundType = GetId("GroundTypeTrail");
        }

        for (auto y = yStart; y <= yEnd; y++)
            mapArea->tiles[xCenter][y].groundType = GetId("GroundTypeCobblestone");

        for (auto x = xStart; x <= xEnd; x++)
            mapArea->tiles[x][yCenter].groundType = GetId("GroundTypeCobblestone");

        for (auto y = yStart; y <= yEnd; y++)
        {
            if (y == yCenter) continue;

            mapArea->tiles[xStart + 1][y].objects.push_back(
                MakeSPtr<Object>("ObjectBush1"));

            mapArea->tiles[xEnd - 1][y].objects.push_back(
                MakeSPtr<Object>("ObjectBush1"));

            mapArea->tiles[xStart][y].objects.push_back(
                MakeSPtr<Object>("ObjectWoodFence", false, false, 180));

            mapArea->tiles[xEnd][y].objects.push_back(
                MakeSPtr<Object>("ObjectWoodFence", false, false, 0));
        }

        for (auto x = xStart; x <= xEnd; x++)
        {
            if (x == xCenter) continue;

            mapArea->tiles[x][yStart + 1].objects.push_back(
                MakeSPtr<Object>("ObjectBush1"));

            mapArea->tiles[x][yEnd - 1].objects.push_back(
                MakeSPtr<Object>("ObjectBush1"));

            mapArea->tiles[x][yStart].objects.push_back(
                MakeSPtr<Object>("ObjectWoodFence", false, false, 90));

            mapArea->tiles[x][yEnd].objects.push_back(
                MakeSPtr<Object>("ObjectWoodFence", false, false, 270));
        }

        auto houseWidth = 4;
        auto houseDepth = 3;

        auto housexCenter = xCenter + 5;
        auto houseyCenter = yCenter + 5;
        auto housexStart = housexCenter - houseWidth / 2;
        auto houseyStart = houseyCenter - houseDepth / 2;
        auto housexEnd = housexStart + houseWidth;
        auto houseyEnd = houseyStart + houseDepth;

        for (auto y = houseyStart - 1; y <= houseyEnd + 1; y++)
        {
            for (auto x = housexStart - 1; x <= housexEnd + 1; x++)
            {
                mapArea->tiles[x][y].elevation = mapArea->tiles[housexCenter][houseyCenter].elevation;
            }
        }

        for (auto y = houseyStart; y <= houseyEnd; y++)
        {
            for (auto x = housexStart; x <= housexEnd; x++)
            {
                mapArea->tiles[x][y].roof = MakeSPtr<Object>("ObjectRoof", false, false);
                mapArea->tiles[x][y].groundType = GetId("GroundTypeWoodfloor");
            }
        }

        for (auto y = houseyStart; y <= houseyEnd; y++)
        {

            mapArea->tiles[housexStart][y].objects.push_back(
                MakeSPtr<Object>("ObjectWoodWall", false, false, 180));

            mapArea->tiles[housexEnd][y].objects.push_back(
                MakeSPtr<Object>("ObjectWoodWall", false, false, 0));
        }

        for (auto x = housexStart; x <= housexEnd; x++)
        {
            if (x != housexCenter)
                mapArea->tiles[x][houseyStart].objects.push_back(
                    MakeSPtr<Object>("ObjectWoodWall", false, false, 90));



            mapArea->tiles[x][houseyEnd].objects.push_back(
                MakeSPtr<Object>("ObjectWoodWall", false, false, 270));
        }

        for (auto y = houseyStart - 1; y != yCenter; y--)
        {
            mapArea->tiles[housexCenter][y].groundType = GetId("GroundTypeCobblestone");
        }

        auto anvilx = xCenter - 5;
        auto anvily = yCenter - 5;

        for (auto y = anvily - 2; y <= anvily + 2; y++)
        {
            for (auto x = anvilx - 2; x <= anvilx + 2; x++)
            {
                mapArea->tiles[x][y].groundType = GetId("GroundTypeCobblestone");
            }
        }

        mapArea->tiles[anvilx][anvily].objects.push_back(
            MakeSPtr<Object>("ObjectLargeAnvil", false));

        mapArea->tiles[xCenter + 1][yCenter - villageSize / 2].objects.push_back(
            MakeSPtr<Object>("ObjectStreetLantern", false));

        mapArea->tiles[xCenter + 1][yCenter + villageSize / 2].objects.push_back(
            MakeSPtr<Object>("ObjectStreetLantern", false));

        mapArea->tiles[xCenter + villageSize / 2][yCenter + 1].objects.push_back(
            MakeSPtr<Object>("ObjectStreetLantern", false));

        mapArea->tiles[xCenter - villageSize / 2][yCenter + 1].objects.push_back(
            MakeSPtr<Object>("ObjectStreetLantern", false));

    }



    int
        ValleyMapGenerator::DistToPlayerStartingPos(MapArea* mapArea, int tileX,
            int tileY) const
    {
        auto DX = mapArea->spawnPos.x - tileX;
        auto DY = mapArea->spawnPos.y - tileY;
        auto Distance = std::sqrt(DX * DX + DY * DY);

        return static_cast<int>(Distance);
    }


    void
        ValleyMapGenerator::GenerateBushes(MapArea* mapArea) const
    {
        for (auto i = 0; i < 200; i++)
        {
            auto tileX = random.Next() % mapArea->size;
            auto tileY = random.Next() % mapArea->size;

            if (DistToPlayerStartingPos(mapArea, tileX, tileY) < playerStartingAreaSize)
                continue;

            if (mapArea->tiles[tileX][tileY].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[tileX][tileY].objects.size() == 0)
                    mapArea->tiles[tileX][tileY].objects.push_back(
                        MakeSPtr<Object>("ObjectBush1"));
        }
    }

    void
        ValleyMapGenerator::GenerateSmallStones(MapArea* mapArea) const
    {
        for (auto i = 0; i < 200; i++)
        {
            auto tileX = random.Next() % mapArea->size;
            auto tileY = random.Next() % mapArea->size;

            if (DistToPlayerStartingPos(mapArea, tileX, tileY) < playerStartingAreaSize)
                continue;

            if (mapArea->tiles[tileX][tileY].groundType != GetId("GroundTypeWater"))
                if (mapArea->tiles[tileX][tileY].objects.size() == 0)
                    mapArea->tiles[tileX][tileY].objects.push_back(
                        MakeSPtr<Object>("ObjectSmallStone"));
        }
    }

    void
        ValleyMapGenerator::GeneratePinkFlowers(MapArea* mapArea) const
    {
        for (auto i = 0; i < 100; i++)
        {
            auto tileX = random.Next() % mapArea->size;
            auto tileY = random.Next() % mapArea->size;

            if (mapArea->tiles[tileX][tileY].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[tileX][tileY].objects.size() == 0)
                    mapArea->tiles[tileX][tileY].objects.push_back(
                        MakeSPtr<Object>("ObjectPinkFlower"));
        }
    }

    void
        ValleyMapGenerator::GenerateTallGrass(MapArea* mapArea) const
    {
        for (auto i = 0; i < 6000; i++)
        {
            auto tileX = random.Next() % mapArea->size;
            auto tileY = random.Next() % mapArea->size;

            if (mapArea->tiles[tileX][tileY].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[tileX][tileY].objects.size() == 0)
                    mapArea->tiles[tileX][tileY].objects.push_back(
                        MakeSPtr<Object>("ObjectTallGrass"));
        }
    }


    void
        ValleyMapGenerator::GenerateMobs(MapArea* mapArea) const
    {
        for (auto i = 0; i < 100; i++)
        {
            auto tileX = random.Next() % mapArea->size;
            auto tileY = random.Next() % mapArea->size;

            if (tileX == static_cast<int>(mapArea->spawnPos.x)
                && tileY == static_cast<int>(mapArea->spawnPos.y))
                continue;

            if (DistToPlayerStartingPos(mapArea, tileX, tileY) < playerStartingAreaSize)
                continue;

            if (mapArea->tiles[tileX][tileY].groundType !=
                GetId("GroundTypeWater") &&
                mapArea->tiles[tileX][tileY].actor == nullptr)
            {
                mapArea->tiles[tileX][tileY].actor =
                    std::make_unique<Mob>(e,
                        static_cast<float>(tileX),
                        static_cast<float>(tileY),
                        "MobRabbit");
                mapArea->mobActorsMirror.insert({ mapArea->tiles[tileX][tileY].actor->actorId,
                            std::ref(mapArea->tiles[tileX][tileY].actor) });
            }
        }

        for (auto i = 0; i < 100; i++)
        {
            auto tileX = random.Next() % mapArea->size;
            auto tileY = random.Next() % mapArea->size;

            if (tileX == static_cast<int>(mapArea->spawnPos.x)
                && tileY == static_cast<int>(mapArea->spawnPos.y))
                continue;

            if (DistToPlayerStartingPos(mapArea, tileX, tileY) < playerStartingAreaSize)
                continue;

            if (mapArea->tiles[tileX][tileY].groundType !=
                GetId("GroundTypeWater") &&
                mapArea->tiles[tileX][tileY].actor == nullptr)
            {
                mapArea->tiles[tileX][tileY].actor =
                    std::make_unique<Mob>(e,
                        static_cast<float>(tileX),
                        static_cast<float>(tileY),
                        "MobRat");
                mapArea->mobActorsMirror.insert({ mapArea->tiles[tileX][tileY].actor->actorId,
                            std::ref(mapArea->tiles[tileX][tileY].actor) });
            }
        }

        for (auto i = 0; i < 100; i++)
        {
            auto tileX = random.Next() % mapArea->size;
            auto tileY = random.Next() % mapArea->size;

            if (tileX == static_cast<int>(mapArea->spawnPos.x)
                && tileY == static_cast<int>(mapArea->spawnPos.y))
                continue;

            if (DistToPlayerStartingPos(mapArea, tileX, tileY) < playerStartingAreaSize)
                continue;

            if (mapArea->tiles[tileX][tileY].groundType !=
                GetId("GroundTypeWater") &&
                mapArea->tiles[tileX][tileY].actor == nullptr)
            {
                mapArea->tiles[tileX][tileY].actor =
                    std::make_unique<Mob>(e,
                        static_cast<float>(tileX),
                        static_cast<float>(tileY),
                        "MobPinkSlime");
                mapArea->mobActorsMirror.insert({ mapArea->tiles[tileX][tileY].actor->actorId,
                            std::ref(mapArea->tiles[tileX][tileY].actor) });
            }
        }
    }

    void
        ValleyMapGenerator::
        GenerateQuestCaves(const IEngine& e,
            MapArea* mapArea,
            const UPtr<PlanetWorldMap>& worldMap) const
    {
        QuestCaveMapGenerator questCaveMapGenerator;

        for (auto floor = -1; floor >= -20; floor--)
        {
            auto tileX = random.Next() % 94 + 3;
            auto tileY = random.Next() % 94 + 3;

            if (DistToPlayerStartingPos(mapArea, tileX, tileY) < playerStartingAreaSize)
                continue;

            auto xCenter = mapArea->size / 2;
            auto yCenter = mapArea->size / 2;
            auto xStartVillage = xCenter - villageSize / 2;
            auto yStartVillage = xCenter - villageSize / 2;
            auto xEndVillage = xStartVillage + villageSize;
            auto yEndVillage = yStartVillage + villageSize;

            if (tileX >= xStartVillage && tileY >= yStartVillage && tileX <= xEndVillage && tileY <= yEndVillage)
                continue;

            if (mapArea->tiles[tileX][tileY].groundType !=
                GetId("GroundTypeWater"))
            {
                mapArea->tiles[tileX][tileY].objects.push_back(
                    MakeSPtr<Object>("ObjectQuestCaveEntrance"));
                //MapArea->Tiles[tileX][tileY].WarpToFloor = Floor;
                mapArea->tiles[tileX][tileY].properties["WarpToFloor"] = std::to_string(floor);

                worldMap->areas[mapArea->worldCoord.x][mapArea->worldCoord.y][floor] =
                    std::make_unique<MapArea>(e, worldMap->mapAreaSize,
                        mapArea->worldCoord.x,
                        mapArea->worldCoord.y,
                        floor);

                auto& questCaveMapArea =
                    worldMap->areas
                    [mapArea->worldCoord.x][mapArea->worldCoord.y][floor];

                questCaveMapGenerator.GenerateQuestCaveMapArea(
                    questCaveMapArea.get(),
                    { tileX, tileY });
            }
        }
    }

}  // namespace Forradia
