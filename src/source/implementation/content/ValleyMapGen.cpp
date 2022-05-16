// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "ValleyMapGen.h"
#include "PlanetWorldMap.h"
#include "Object.h"
#include "QuestCaveMapGen.h"

namespace Forradia
{

    void ValleyMapGen::GenerateMapArea(Point3 worldPos) const
    {
        worldMap->areas[worldPos.x][worldPos.y][worldPos.z] =  MakeUPtr<MapArea>(e, worldMap->mapAreaSize, worldPos);

        auto mapArea = worldMap->GetArea(worldPos).get();

        ClearToGrass(mapArea);
        GeneratePlayerStartingPosition(mapArea);
        GenerateRivers(mapArea);
        GenerateElevation(mapArea);
        //GenerateRock(mapArea);
        GenerateTrees(mapArea);
        GenerateBushes(mapArea);
        GenerateSmallStones(mapArea);
        GeneratePinkFlowers(mapArea);
        GenerateTallGrass(mapArea);
        GenerateVillage(mapArea);
        GenerateMobs(mapArea);
        GenerateQuestCaves(e, mapArea, worldMap);
    }

    void ValleyMapGen::ClearToGrass(MapArea* mapArea) const
    {
        for (auto tile : mapArea->AllTiles())
            tile.get().groundType = GetId("GroundTypeGrass");
    }

    void ValleyMapGen::GeneratePlayerStartingPosition(MapArea* mapArea) const
    {
        mapArea->spawnPos = { CFloat(mapArea->size / 2), CFloat(mapArea->size / 2) };
    }

    void ValleyMapGen::GenerateElevation(MapArea* mapArea) const
    {
        //for (auto y = 0; y < mapArea->size; y++)
        //{
        //    for (auto x = 0; x < mapArea->size; x++)
        //    {
        //        auto dxLeft = x;
        //        auto dxRight = mapArea->size - x;
        //        auto dyTop = y;
        //        auto dyBottom = mapArea->size - y;

        //        auto elevHorizontal = std::max(dxLeft, dxRight);
        //        auto elevVertical = std::max(dyTop, dyBottom);
        //        auto elev = std::max(std::max(elevHorizontal, elevVertical), 86) * 5 - 40;
        //        elev = std::min(elev, 440);

        //        mapArea->tiles[x][y].elevation = elev / 1.5f;

        //    }
        //}

        for (auto i = 0; i < 160; i++)
        {
            auto centerTileX = 0;
            auto centerTileY = 0;
            auto maxr = 4 + rnd.Next(6);

            do
            {
                centerTileX = rnd.Next(mapArea->size);
                centerTileY = rnd.Next(mapArea->size);
                maxr = 5 + rnd.Next(12);
            } while (std::abs(centerTileX - mapArea->size / 2) < villageSize
                || std::abs(centerTileY - mapArea->size / 2) < villageSize);

            auto stop = false;

            auto angle = rnd.Next(360) / 180.0f * M_PI;
            auto dirx = std::cosf(angle);
            auto diry = std::sinf(angle);

            for (auto r = maxr; r >= 0 && !stop; r-= 1)
            {
                for (auto y = centerTileY - r; y <= centerTileY + r && !stop; y++)
                {
                    for (auto x = centerTileX - r; x <= centerTileX + r && !stop; x++)
                    {
                        auto dx = x - centerTileX;
                        auto dy = y - centerTileY;

                        if (dx * dx + dy * dy >= r * r) continue;
                        if (x < 0 || y < 0 || x >= mapArea->size - 1 || y >= mapArea->size - 1) continue;

                        if (mapArea->tiles[x][y].groundType == GetId("GroundTypeWater")) stop = true;

                        mapArea->tiles[x][y].elevation += 2;

                        auto param = std::powf(1.0f * (maxr - r), 2) / (1.0f*maxr)/2.0f;
                        mapArea->tiles[x][y].vertexOffset =
                        {
                        (rnd.Next(2) - 1) / 6.0f + dirx * param,
                        (rnd.Next(2) - 1) / 6.0f + diry * param
                        };
                    }
                }
            }
        }

        for (auto i = 0; i < 160; i++)
        {
            auto centerTileX = 0;
            auto centerTileY = 0;
            auto maxr = 4 + rnd.Next(6);

            do
            {
                centerTileX = rnd.Next(mapArea->size);
                centerTileY = rnd.Next(mapArea->size);
                maxr = 1 + rnd.Next(6);
            } while (std::abs(centerTileX - mapArea->size / 2) < villageSize
                || std::abs(centerTileY - mapArea->size / 2) < villageSize);

            auto stop = false;

            auto angle = rnd.Next(360)/180.0f*M_PI;
            auto dirx = std::cosf(angle);
            auto diry = std::sinf(angle);

            for (auto r = maxr; r >= 0 && !stop; r-= 1)
            {
                for (auto y = centerTileY - r; y <= centerTileY + r && !stop; y++)
                {
                    for (auto x = centerTileX - r; x <= centerTileX + r && !stop; x++)
                    {
                        auto dx = x - centerTileX;
                        auto dy = y - centerTileY;

                        if (dx * dx + dy * dy >= r * r) continue;
                        if (x < 0 || y < 0 || x >= mapArea->size - 1 || y >= mapArea->size - 1) continue;
                        if (mapArea->tiles[x][y].groundType == GetId("GroundTypeWater")) stop = true;

                        mapArea->tiles[x][y].elevation += 5;
                        mapArea->tiles[x][y].groundType = GetId("GroundTypeRock");
                        mapArea->tiles[x+1][y].groundType = GetId("GroundTypeRock");
                        mapArea->tiles[x][y+1].groundType = GetId("GroundTypeRock");
                        mapArea->tiles[x+1][y+1].groundType = GetId("GroundTypeRock");

                        auto param = std::powf(1.0f * (maxr - r), 2) / (1.0f * maxr) / 2.0f;
                        mapArea->tiles[x][y].vertexOffset =
                        {
                        (rnd.Next(2) - 1) / 6.0f + dirx * param,
                        (rnd.Next(2) - 1) / 6.0f + diry * param
                        };
                    }
                }
            }
        }

    }

    void ValleyMapGen::GenerateRock(MapArea* mapArea) const
    {
        for (auto i = 0; i < 30; i++)
        {

            auto centerx = 0;
            auto centery = 0;
            auto r = 0;

            do
            {

                centerx = rnd.Next(mapArea->size);
                centery = rnd.Next(mapArea->size);
                r = 5 + rnd.Next(13);

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

    void ValleyMapGen::GenerateRivers(MapArea* mapArea) const
    {
        for (auto i = 0; i < 6; i++)
        {
            float xstart = rnd.Next(mapArea->size);
            float ystart = rnd.Next(mapArea->size);

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

                if (xi >= 1 && yi >= 0 && xi < mapArea->size && yi < mapArea->size - 1)
                {
                    mapArea->tiles[xi][yi].groundType = GetId("GroundTypeWater");
                    mapArea->tiles[xi - 1][yi].elevation = mapArea->tiles[xi][yi].elevation;
                    mapArea->tiles[xi][yi + 1].elevation = mapArea->tiles[xi][yi].elevation;
                    mapArea->tiles[xi - 1][yi + 1].elevation = mapArea->tiles[xi][yi].elevation;
                }
            }
        }
    }

    void ValleyMapGen::GenerateTrees(MapArea* mapArea) const
    {
        for (auto i = 0; i < 30; i++)
        {
            auto x = rnd.Next(mapArea->size);
            auto y = rnd.Next(mapArea->size);
            auto numTrees = 15 + rnd.Next(15);

            for (auto j = 0; j < numTrees; j++)
            {
                if (x >= 0 && y >= 0 && x < mapArea->size && y < mapArea->size)
                {
                    if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

                    if (mapArea->tiles[x][y].groundType == GetId("GroundTypeGrass"))
                        if (mapArea->tiles[x][y].objects.size() == 0)
                            mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectTree1", true, true));
                }

                x += rnd.Next(7) - rnd.Next(7);
                y += rnd.Next(7) - rnd.Next(7) ;
            }
        }
        for (auto i = 0; i < 30; i++)
        {
            auto x = rnd.Next(mapArea->size);
            auto y = rnd.Next(mapArea->size);
            auto numTrees = 15 + rnd.Next(15);

            for (auto j = 0; j < numTrees; j++)
            {
                if (x >= 0 && y >= 0 && x < mapArea->size && y < mapArea->size)
                {
                    if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

                    if (mapArea->tiles[x][y].groundType == GetId("GroundTypeGrass"))
                        if (mapArea->tiles[x][y].objects.size() == 0)
                            mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectTree2", true, true));
                }

                x += rnd.Next(7) - rnd.Next(7);
                y += rnd.Next(7) - rnd.Next(7);
            }
        }
        for (auto i = 0; i < 90; i++)
        {
            auto x = rnd.Next(mapArea->size);
            auto y = rnd.Next(mapArea->size);
            auto numTrees = 1 + rnd.Next(4);

            for (auto j = 0; j < numTrees; j++)
            {
                if (x >= 0 && y >= 0 && x < mapArea->size && y < mapArea->size)
                {
                    if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

                    if (mapArea->tiles[x][y].groundType == GetId("GroundTypeGrass"))
                        if (mapArea->tiles[x][y].objects.size() == 0)
                            mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectRipeAppleTree", true, true));
                }

                x += rnd.Next(7) - rnd.Next(7);
                y += rnd.Next(7) - rnd.Next(7);
            }
        }
    }

    void ValleyMapGen::GenerateVillage(MapArea* mapArea) const
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
                mapArea->tiles[x][y].elevation = 0;
            }
        }

        for (auto y = ycenter - 1; y <= ycenter + 1; y++)
        {
            for (auto x = xcenter - 1; x <= xcenter + 1; x++)
            {
                mapArea->tiles[x][y].groundType = GetId("GroundTypeCobblestone");
            }
        }

        auto xoffset = 0;

        for (auto y = 0; y < mapArea->size/2; y++)
        {
            mapArea->tiles[xcenter + xoffset][ycenter + y].objects.clear();
            mapArea->tiles[xcenter + xoffset][ycenter + y].groundType = GetId("GroundTypeTrail");
            mapArea->tiles[xcenter + xoffset][ycenter - y].objects.clear();
            mapArea->tiles[xcenter + xoffset][ycenter - y].groundType = GetId("GroundTypeTrail");

            if (y % 3 == 0 && y >= villageSize)
                xoffset += rnd.Next(2) - rnd.Next(2);

            mapArea->tiles[xcenter + xoffset][ycenter + y].objects.clear();
            mapArea->tiles[xcenter + xoffset][ycenter + y].groundType = GetId("GroundTypeTrail");
            mapArea->tiles[xcenter + xoffset][ycenter - y].objects.clear();
            mapArea->tiles[xcenter + xoffset][ycenter - y].groundType = GetId("GroundTypeTrail");
        }

        auto yoffset = 0;

        for (auto x = 0; x < mapArea->size/2; x++)
        {
            mapArea->tiles[xcenter + x][ycenter + yoffset].objects.clear();
            mapArea->tiles[xcenter + x][ycenter + yoffset].groundType = GetId("GroundTypeTrail");
            mapArea->tiles[xcenter - x][ycenter + yoffset].objects.clear();
            mapArea->tiles[xcenter - x][ycenter + yoffset].groundType = GetId("GroundTypeTrail");

            if (x % 3 == 0 && x >= villageSize)
                yoffset += rnd.Next(2) - rnd.Next(2);

            mapArea->tiles[xcenter + x][ycenter + yoffset].objects.clear();
            mapArea->tiles[xcenter + x][ycenter + yoffset].groundType = GetId("GroundTypeTrail");
            mapArea->tiles[xcenter - x][ycenter + yoffset].objects.clear();
            mapArea->tiles[xcenter - x][ycenter + yoffset].groundType = GetId("GroundTypeTrail");
        }

        for (auto y = ystart; y <= yend; y++)
            mapArea->tiles[xcenter][y].groundType = GetId("GroundTypeCobblestone");

        for (auto x = xstart; x <= xend; x++)
            mapArea->tiles[x][ycenter].groundType = GetId("GroundTypeCobblestone");

        for (auto y = ystart; y <= yend; y++)
        {
            if (y == ycenter) continue;

            mapArea->tiles[xstart][y].objects.push_back(MakeSPtr<Object>("ObjectBush1", true, true));
            mapArea->tiles[xend][y].objects.push_back(MakeSPtr<Object>("ObjectBush1", true, true));
            mapArea->tiles[xstart][y].objects.push_back(MakeSPtr<Object>("ObjectWoodFence", false, false, 180));
            mapArea->tiles[xend][y].objects.push_back(MakeSPtr<Object>("ObjectWoodFence", false, false, 0));
        }

        for (auto x = xstart; x <= xend; x++)
        {
            if (x == xcenter) continue;

            mapArea->tiles[x][ystart].objects.push_back(MakeSPtr<Object>("ObjectBush1", true, true));
            mapArea->tiles[x][yend].objects.push_back(MakeSPtr<Object>("ObjectBush1", true, true));
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

    int ValleyMapGen::DistToPlayerStartingPos(MapArea* mapArea, int tileX, int tileY) const
    {
        auto dx = mapArea->spawnPos.x - tileX;
        auto dy = mapArea->spawnPos.y - tileY;
        auto distance = std::sqrt(dx * dx + dy * dy);

        return CInt(distance);
    }


    void ValleyMapGen::GenerateBushes(MapArea* mapArea) const
    {
        for (auto i = 0; i < 1000; i++)
        {
            auto tileX = rnd.Next(mapArea->size);
            auto tileY = rnd.Next(mapArea->size);

            if (DistToPlayerStartingPos(mapArea, tileX, tileY) < playerStartAreaSize) continue;

            if (mapArea->tiles[tileX][tileY].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[tileX][tileY].objects.size() == 0)
                    mapArea->tiles[tileX][tileY].objects.push_back(MakeSPtr<Object>("ObjectBush1", true, true));
        }
    }

    void ValleyMapGen::GenerateSmallStones(MapArea* mapArea) const
    {
        for (auto i = 0; i < 200; i++)
        {
            auto x = rnd.Next(mapArea->size);
            auto y = rnd.Next(mapArea->size);

            if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

            if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater"))
                if (mapArea->tiles[x][y].objects.size() == 0)
                    mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectSmallStone"));
        }
    }

    void ValleyMapGen::GeneratePinkFlowers(MapArea* mapArea) const
    {
        for (auto i = 0; i < 100; i++)
        {
            auto x = rnd.Next(mapArea->size);
            auto y = rnd.Next(mapArea->size);

            if (mapArea->tiles[x][y].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[x][y].objects.size() == 0)
                    mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectPinkFlower"));
        }
    }

    void ValleyMapGen::GenerateTallGrass(MapArea* mapArea) const
    {
        for (auto i = 0; i < 6000; i++)
        {
            auto x = rnd.Next(mapArea->size);
            auto y = rnd.Next(mapArea->size);

            if (mapArea->tiles[x][y].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[x][y].objects.size() == 0)
                    mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectTallGrass", true, true));
        }
    }


    void ValleyMapGen::GenerateMobs(MapArea* mapArea) const
    {
        for (auto i = 0; i < 100; i++)
        {
            auto x = rnd.Next(mapArea->size);
            auto y = rnd.Next(mapArea->size);

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
            auto x = rnd.Next(mapArea->size);
            auto y = rnd.Next(mapArea->size);

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
            auto x = rnd.Next(mapArea->size);
            auto y = rnd.Next(mapArea->size);

            if (x == CInt(mapArea->spawnPos.x) && y == CInt(mapArea->spawnPos.y)) continue;
            if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

            if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater") && mapArea->tiles[x][y].actor == nullptr)
            {
                mapArea->tiles[x][y].actor = MakeUPtr<Mob>(e, CFloat(x), CFloat(y), "MobTroll");
                mapArea->mobActorsMirror.insert({ mapArea->tiles[x][y].actor->actorId, std::ref(mapArea->tiles[x][y].actor) });
            }
        }

        //for (auto i = 0; i < 100; i++)
        //{
        //    auto x = rnd.Next() % mapArea->size;
        //    auto y = rnd.Next() % mapArea->size;

        //    if (x == CInt(mapArea->spawnPos.x) && y == CInt(mapArea->spawnPos.y)) continue;
        //    if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

        //    if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater") && mapArea->tiles[x][y].actor == nullptr)
        //    {
        //        mapArea->tiles[x][y].actor = MakeUPtr<Mob>(e, CFloat(x), CFloat(y), "MobPinkSlime");
        //        mapArea->mobActorsMirror.insert({ mapArea->tiles[x][y].actor->actorId, std::ref(mapArea->tiles[x][y].actor) });
        //    }
        //}

        auto x = 0;
        auto y = 0;

        x = rnd.Next(mapArea->size);
        y = rnd.Next(mapArea->size);

        mapArea->tiles[x][y].actor = MakeUPtr<Mob>(e, CFloat(x), CFloat(y), "MobRubyButterfly");
        mapArea->mobActorsMirror.insert({ mapArea->tiles[x][y].actor->actorId, std::ref(mapArea->tiles[x][y].actor) });

        x = rnd.Next(mapArea->size);
        y = rnd.Next(mapArea->size);

        mapArea->tiles[x][y].actor = MakeUPtr<Mob>(e, CFloat(x), CFloat(y), "MobTopazButterfly");
        mapArea->mobActorsMirror.insert({ mapArea->tiles[x][y].actor->actorId, std::ref(mapArea->tiles[x][y].actor) });

        x = rnd.Next(mapArea->size);
        y = rnd.Next(mapArea->size);

        mapArea->tiles[x][y].actor = MakeUPtr<Mob>(e, CFloat(x), CFloat(y), "MobJadeButterfly");
        mapArea->mobActorsMirror.insert({ mapArea->tiles[x][y].actor->actorId, std::ref(mapArea->tiles[x][y].actor) });

        x = rnd.Next(mapArea->size);
        y = rnd.Next(mapArea->size);

        mapArea->tiles[x][y].actor = MakeUPtr<Mob>(e, CFloat(x), CFloat(y), "MobAmberButterfly");
        mapArea->mobActorsMirror.insert({ mapArea->tiles[x][y].actor->actorId, std::ref(mapArea->tiles[x][y].actor) });
    }

    void ValleyMapGen::GenerateQuestCaves(const IEngine& e, MapArea* mapArea, const UPtr<PlanetWorldMap>& worldMap) const
    {
        QuestCaveMapGen questCaveMapGen;

        for (auto floor = -1; floor >= -5; floor--)
        {
            auto x = rnd.Next(94) + 3;
            auto y = rnd.Next(94) + 3;

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

                questCaveMapGen.GenerateQuestCaveMapArea(questCaveMapArea.get(), { x, y });
            }
        }
    }

}  // namespace Forradia
