// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "QuestCaveMapGen.h"
#include "framework/worldStructure/Object.h"

namespace Forradia
{

    void QuestCaveMapGen::GenerateQuestCaveMapArea(MapArea* mapArea, Point2 entranceLoc)
    {
        ClearToCaveFloor(mapArea);
        GenerateCaveWalls(mapArea);
        GeneratePath(mapArea, entranceLoc);

        mapArea->tiles[entranceLoc.x][entranceLoc.y].properties["WarpToFloor"] = "0";
        mapArea->tiles[entranceLoc.x][entranceLoc.y].objects.push_back(MakeSPtr<Object>("ObjectQuestCaveEntrance"));
    }

    void QuestCaveMapGen::ClearToCaveFloor(MapArea* mapArea)
    {
        for (auto y = 0; y < mapArea->size; y++)
            for (auto x = 0; x < mapArea->size; x++)
                mapArea->tiles[x][y].groundType = GetId("GroundTypeCaveFloor");
    }

    void QuestCaveMapGen::GenerateCaveWalls(MapArea* mapArea)
    {
        for (auto y = 0; y < mapArea->size; y++)
            for (auto x = 0; x < mapArea->size; x++)
                mapArea->tiles[x][y].objects.push_back(MakeSPtr<Object>("ObjectCaveWallBlock", false));
    }

    void QuestCaveMapGen::GeneratePath(MapArea* mapArea, Point2 entranceLoc)
    {
        for (auto y = entranceLoc.y - 3; y <= entranceLoc.y + 3; y++)
            for (auto x = entranceLoc.x - 3; x <= entranceLoc.x + 3; x++)
                mapArea->tiles[x][y].objects.clear();

        auto x = entranceLoc.x;
        auto y = entranceLoc.y;

        for (auto i = 0; i < 20; i++)
        {
            auto direction = rnd.Next() % 4;
            auto numSteps = 4 + rnd.Next() % 20;

            for (auto j = 0; j < numSteps; j++)
            {
                for (auto xx = x - 1; xx <= x + 1; xx++)
                {
                    for (auto yy = y - 1; yy <= y + 1; yy++)
                    {
                        if (xx >= 0 && yy >= 0 && xx < mapArea->size && yy < mapArea->size)
                            if (mapArea->tiles[xx][yy].objects.size() > 0)
                                if (!mapArea->tiles[xx][yy].HasObjectOfType("ObjectQuestCaveEntrance"))
                                    mapArea->tiles[xx][yy].objects.clear();
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

}  // namespace Forradia
