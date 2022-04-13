// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Random.h"
#include "../engine/MapArea.h"
#include "../engine/Point2.h"

namespace Forradia
{

    class QuestCaveMapGenerator
    {
    public:
        void GenerateQuestCaveMapArea(MapArea* mapArea, Point2 entranceLocation);

    private:
        void ClearToCaveFloor(MapArea* mapArea);
        void GenerateCaveWalls(MapArea* mapArea);
        void GeneratePath(MapArea* mapArea, Point2 entranceLocation);

        Random rnd;
    };

}  // namespace Forradia
