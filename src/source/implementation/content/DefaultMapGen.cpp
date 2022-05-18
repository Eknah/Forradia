// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "DefaultMapGen.h"
#include "QuestCaveMapGen.h"
#include "PlanetWorldMap.h"
#include "Object.h"
#include "Aliases.h"

namespace Forradia
{

    void DefaultMapGen::GenerateMapArea(Point3 worldPos) const
    {
        worldMap->areas[worldPos.x][worldPos.y][worldPos.z] = MakeUPtr<MapArea>(e, worldMap->mapAreaSize, worldPos);

        auto mapArea = worldMap->GetArea(worldPos).get();

        ClearToGrass(mapArea);
        GeneratePlayerStartingPosition(mapArea);
        GenerateWater(mapArea);
        GenerateElevation(mapArea);
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

    void DefaultMapGen::ClearToGrass(MapArea* mapArea) const
    {
        for (auto tile : mapArea->AllTiles())
            tile.get().groundType = GetId("GroundTypeGrass");
    }

    void DefaultMapGen::GeneratePlayerStartingPosition(MapArea* mapArea) const
    {
        mapArea->spawnPos = mapArea->RandCoordF();
    }


    void DefaultMapGen::GenerateWater(MapArea* mapArea) const
    {
        for (auto i = 0; i < 20; i++)
        {
            auto center = mapArea->RandCoordI();
            auto r = 10 + rnd.Next(13);
            auto kx = rnd.Next(10)/10.0f;
            auto ky = rnd.Next(10)/10.0f;

            for (auto y = center.y - r; y <= center.y + r; y++)
            {
                for (auto x = center.x - r; x <= center.x + r; x++)
                {
                    auto dx = x - center.x;
                    auto dy = y - center.y;

                    if (dx*dx*kx + dy * dy *ky>= r) continue;
                    if (!mapArea->Contains({ x, y }, 1)) continue;
                    if (mapArea->tiles[x][y].elevation > 0) continue;
                    if (mapArea->tiles[x - 1][y].elevation > 0) continue;
                    if (mapArea->tiles[x - 1][y - 1].elevation > 0) continue;
                    if (mapArea->tiles[x][y - 1].elevation > 0) continue;
                    if (mapArea->tiles[x + 1][y].elevation > 0) continue;
                    if (mapArea->tiles[x + 1][y + 1].elevation > 0) continue;
                    if (mapArea->tiles[x][y + 1].elevation > 0) continue;
                    if (mapArea->tiles[x - 1][y + 1].elevation > 0) continue;
                    if (mapArea->tiles[x + 1][y - 1].elevation > 0) continue;
                    if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

                    mapArea->tiles[x][y].groundType = GetId("GroundTypeWater");
                }
            }
        }
    }

    void DefaultMapGen::GenerateElevation(MapArea* mapArea) const
    {
        for (auto i = 0; i < 400; i++)
        {
            auto center =mapArea->RandCoordI();
            auto maxr = 4 + rnd.Next(12);
            auto rDecr = 1 + rnd.Next(6);

            for (auto r = maxr; r >= 0; r -= rDecr)
            {
                for (auto y = center.y - r; y <= center.y + r; y++)
                {
                    for (auto x = center.x - r; x <= center.x + r; x++)
                    {
                        auto dx = x - center.x;
                        auto dy = y - center.y;

                        if (!mapArea->Contains({x, y})) continue;
                        if (mapArea->tiles[x][y].elevation + 2 >= mapArea->GetTile(center).elevation + 2*(r-1)) continue;
                        if (mapArea->tiles[x][y].groundType == GetId("GroundTypeWater")) continue;

                        if (x < mapArea->size - 1)
                            if (mapArea->tiles[x][y].elevation > mapArea->tiles[x+1][y].elevation) continue;
                        if (x < mapArea->size - 1 && y < mapArea->size - 1)
                            if (mapArea->tiles[x][y].elevation > mapArea->tiles[x+1][y+1].elevation) continue;
                        if (y < mapArea->size - 1)
                            if (mapArea->tiles[x][y].elevation > mapArea->tiles[x][y+1].elevation) continue;
                        if (x > 0 && y < mapArea->size - 1)
                            if (mapArea->tiles[x][y].elevation > mapArea->tiles[x-1][y+1].elevation) continue;
                        if (x > 0)
                            if (mapArea->tiles[x][y].elevation > mapArea->tiles[x-1][y].elevation) continue;
                        if (x > 0 && y >  0)
                            if (mapArea->tiles[x][y].elevation > mapArea->tiles[x-1][y-1].elevation) continue;
                        if (y > 0)
                            if (mapArea->tiles[x][y].elevation > mapArea->tiles[x][y-1].elevation) continue;
                        if (y > 0 && x < mapArea->size - 1)
                            if (mapArea->tiles[x][y].elevation > mapArea->tiles[x+1][y-1].elevation) continue;

                        mapArea->tiles[x][y].elevation += 2;
                    }
                }
            }
        }
    }


    void DefaultMapGen::GenerateSand(MapArea* mapArea) const
    {
        for (auto i = 0; i < 30; i++)
        {
            auto center = mapArea->RandCoordI();
            auto r = 4 + rnd.Next(5);

            for (auto j = 0; j < r; j++)
            {
                for (auto y = center.y - r; y <= center.y + r; y++)
                {
                    for (auto x = center.x - r; x <= center.x + r; x++)
                    {
                        auto dx = x - center.x;
                        auto dy = y - center.y;

                        if (dx * dx + dy * dy >= r * r) continue;
                        if (!mapArea->Contains({ x, y }, 1)) continue;
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

    void DefaultMapGen::GenerateClay(MapArea* mapArea) const
    {
        for (auto i = 0; i < 30; i++)
        {
            auto center = mapArea->RandCoordI();
            auto r = 2 + rnd.Next(3);

            for (auto j = 0; j < r; j++)
            {
                for (auto y = center.y - r; y <= center.y + r; y++)
                {
                    for (auto x = center.x - r; x <= center.x + r; x++)
                    {
                        auto dx = x - center.x;
                        auto dy = y - center.y;

                        if (dx * dx + dy * dy >= r * r) continue;
                        if (!mapArea->Contains({ x, y }, 1)) continue;
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

    void DefaultMapGen::GenerateRock(MapArea* mapArea) const
    {
        for (auto i = 0; i < 10; i++)
        {
            auto center = mapArea->RandCoordI();
            auto r = 5 + rnd.Next(13);

            for (auto y = center.y - r; y <= center.y + r; y++)
            {
                for (auto x = center.x - r; x <= center.x + r; x++)
                {
                    auto dx = x - center.x;
                    auto dy = y - center.y;

                    if (dx * dx + dy * dy >= r * r) continue;
                    if (!mapArea->Contains({ x, y })) continue;
                    if (mapArea->tiles[x][y].elevation < 4) continue;

                    mapArea->tiles[x][y].groundType = GetId("GroundTypeRock");
                }
            }
        }
    }

    void DefaultMapGen::GenerateTrees(MapArea* mapArea) const
    {
        for (auto i = 0; i < 30; i++)
        {
            auto coord = mapArea->RandCoordI();
            auto numTrees = 15 + rnd.Next(15);

            for (auto j = 0; j < numTrees; j++)
            {
                if (mapArea->Contains(coord))
                {
                    if (DistToPlayerStartingPos(mapArea, coord.x, coord.y) < playerStartAreaSize) continue;

                    if (mapArea->tiles[coord.x][coord.y].groundType == GetId("GroundTypeGrass"))
                        if (mapArea->tiles[coord.x][coord.y].objects.size() == 0)
                            mapArea->tiles[coord.x][coord.y].objects.push_back(MakeSPtr<Object>("ObjectTree1"));
                }

                coord.x += rnd.Next(7) - rnd.Next(7);
                coord.y += rnd.Next(7) - rnd.Next(7);
            }
        }
        for (auto i = 0; i < 30; i++)
        {
            auto coord = mapArea->RandCoordI();
            auto numTrees = 15 + rnd.Next(15);

            for (auto j = 0; j < numTrees; j++)
            {
                if (mapArea->Contains(coord))
                {
                    if (DistToPlayerStartingPos(mapArea, coord.x, coord.y) < playerStartAreaSize) continue;

                    if (mapArea->tiles[coord.x][coord.y].groundType == GetId("GroundTypeGrass"))
                        if (mapArea->tiles[coord.x][coord.y].objects.size() == 0)
                            mapArea->tiles[coord.x][coord.y].objects.push_back(MakeSPtr<Object>("ObjectTree2"));
                }

                coord.x += rnd.Next(7) - rnd.Next(7);
                coord.y += rnd.Next(7) - rnd.Next(7);
            }
        }
    }

    void DefaultMapGen::GenerateBushes(MapArea* mapArea) const
    {
        for (auto i = 0; i < 200; i++)
        {
            auto coord = mapArea->RandCoordI();

            if (DistToPlayerStartingPos(mapArea, coord.x, coord.y) < playerStartAreaSize) continue;

            if (mapArea->tiles[coord.x][coord.y].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[coord.x][coord.y].objects.size() == 0)
                    mapArea->tiles[coord.x][coord.y].objects.push_back(MakeSPtr<Object>("ObjectBush1"));
        }
    }

    void DefaultMapGen::GenerateSmallStones(MapArea* mapArea) const
    {
        for (auto i = 0; i < 200; i++)
        {
            auto coord = mapArea->RandCoordI();

            if (DistToPlayerStartingPos(mapArea, coord.x, coord.y) < playerStartAreaSize) continue;

            if (mapArea->tiles[coord.x][coord.y].groundType != GetId("GroundTypeWater"))
                if (mapArea->tiles[coord.x][coord.y].objects.size() == 0)
                    mapArea->tiles[coord.x][coord.y].objects.push_back(MakeSPtr<Object>("ObjectSmallStone"));
        }
    }

    void DefaultMapGen::GeneratePinkFlowers(MapArea* mapArea) const
    {
        for (auto i = 0; i < 100; i++)
        {
            auto coord = mapArea->RandCoordI();

            if (mapArea->tiles[coord.x][coord.y].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[coord.x][coord.y].objects.size() == 0)
                    mapArea->tiles[coord.x][coord.y].objects.push_back(MakeSPtr<Object>("ObjectPinkFlower"));
        }
    }

    void DefaultMapGen::GenerateTallGrass(MapArea* mapArea) const
    {
        for (auto i = 0; i < 1000; i++)
        {
            auto coord = mapArea->RandCoordI();

            if (mapArea->tiles[coord.x][coord.y].groundType == GetId("GroundTypeGrass"))
                if (mapArea->tiles[coord.x][coord.y].objects.size() == 0)
                    mapArea->tiles[coord.x][coord.y].objects.push_back(MakeSPtr<Object>("ObjectTallGrass"));
        }
    }

    int DefaultMapGen::DistToPlayerStartingPos(MapArea* mapArea, int tileX, int tileY) const
    {
        auto dx = mapArea->spawnPos.x - tileX;
        auto dy = mapArea->spawnPos.y - tileY;
        auto distance = std::sqrt(dx * dx + dy * dy);

        return CInt(distance);
    }

    void DefaultMapGen::GenerateMobs(MapArea* mapArea) const
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

    void DefaultMapGen::GenerateQuestCaves(const IEngine& e, MapArea* mapArea, const UPtr<PlanetWorldMap>& worldMap) const
    {
        QuestCaveMapGen questCaveMapGen;

        for (auto floor = -1; floor >= -20; floor--)
        {
            auto x = rnd.Next(94) + 3;
            auto y = rnd.Next(94) + 3;

            if (DistToPlayerStartingPos(mapArea, x, y) < playerStartAreaSize) continue;

            if (mapArea->tiles[x][y].groundType != GetId("GroundTypeWater"))
            {
                mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectQuestCaveEntrance"));
                mapArea->tiles[x][y].properties["WarpToFloor"] = std::to_string(floor);

                worldMap->areas[mapArea->worldCoord.x][mapArea->worldCoord.y][floor] = MakeUPtr<MapArea>(e, worldMap->mapAreaSize, Point3 { mapArea->worldCoord.x, mapArea->worldCoord.y, floor });

                auto& questCaveMapArea = worldMap->areas[mapArea->worldCoord.x][mapArea->worldCoord.y][floor];

                questCaveMapGen.GenerateQuestCaveMapArea(questCaveMapArea.get(), { x, y });
            }
        }
    }

}  // namespace Forradia
