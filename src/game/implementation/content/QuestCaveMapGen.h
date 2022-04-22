// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "../engine/Random.h"
#include "../engine/MapArea.h"
#include "../engine/Point2.h"

namespace Forradia
{

    class QuestCaveMapGen
    {

        // Functions

    public:

        void GenerateQuestCaveMapArea(MapArea* mapArea, Point2 entranceLoc);

    private:

        void ClearToCaveFloor(MapArea* mapArea);
        void GenerateCaveWalls(MapArea* mapArea);
        void GeneratePath(MapArea* mapArea, Point2 entranceLoc);

        // Members

    private:
        Random rnd;

    };

}  // namespace Forradia
