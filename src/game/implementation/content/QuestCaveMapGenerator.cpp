// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "QuestCaveMapGenerator.h"
#include "framework/worldStructure/Object.h"

namespace Forradia
{

    void QuestCaveMapGenerator::GenerateQuestCaveMapArea(MapArea* mapArea, Point2 entranceLocation)
    {
        ClearToCaveFloor(mapArea);
        GenerateCaveWalls(mapArea);
        GeneratePath(mapArea, entranceLocation);

        mapArea->tiles[entranceLocation.x][entranceLocation.y].properties["WarpToFloor"] = "0";
        mapArea->tiles[entranceLocation.x][entranceLocation.y].objects.push_back(
            MakeSPtr<Object>("ObjectQuestCaveEntrance"));
    }

    void QuestCaveMapGenerator::ClearToCaveFloor(MapArea* mapArea)
    {
        for (auto tileY = 0; tileY < mapArea->size; tileY++)
            for (auto tileX = 0; tileX < mapArea->size; tileX++)

                mapArea->tiles[tileX][tileY].groundType = GetId("GroundTypeCaveFloor");
    }

    void QuestCaveMapGenerator::GenerateCaveWalls(MapArea* mapArea)
    {
        for (auto tileY = 0; tileY < mapArea->size; tileY++)
            for (auto tileX = 0; tileX < mapArea->size; tileX++)

                mapArea->tiles[tileX][tileY].objects.push_back(
                    MakeSPtr<Object>("ObjectCaveWallBlock", false));
    }

    void QuestCaveMapGenerator::GeneratePath(MapArea* mapArea, Point2 entranceLocation)
    {
        for (auto tileY = entranceLocation.y - 3; tileY <= entranceLocation.y + 3;
            tileY++)
            for (auto tileX = entranceLocation.x - 3; tileX <= entranceLocation.x + 3;
                tileX++)

                mapArea->tiles[tileX][tileY].objects.clear();

        auto tileX = entranceLocation.x;
        auto tileY = entranceLocation.y;

        for (auto i = 0; i < 20; i++)
        {
            auto direction = random.Next() % 4;
            auto numSteps = 4 + random.Next() % 20;

            for (auto j = 0; j < numSteps; j++)
            {
                for (auto xx = tileX - 1; xx <= tileX + 1; xx++)
                {
                    for (auto yy = tileY - 1; yy <= tileY + 1; yy++)
                    {
                        if (xx >= 0 && yy >= 0 && xx < mapArea->size && yy < mapArea->size)
                            if (mapArea->tiles[xx][yy].objects.size() > 0)
                                if (!mapArea->tiles[xx][yy].HasObjectOfType(
                                    "ObjectQuestCaveEntrance"))
                                    mapArea->tiles[xx][yy].objects.clear();
                    }
                }

                switch (direction)
                {
                case 0:
                {
                    tileX++;

                    break;
                }
                case 1:
                {
                    tileY++;

                    break;
                }
                case 2:
                {
                    tileX--;

                    break;
                }
                case 3:
                {
                    tileY--;

                    break;
                }
                }
            }
        }
    }

}  // namespace Forradia
