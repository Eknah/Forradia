// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "MapArea.h"
#include "Rect.h"

namespace Forradia
{

    class IMapGenerator;

    class PlanetWorldMap
    {
    public:
        explicit PlanetWorldMap(int _mapAreaSize, int _worldMapWidth, int _worldMapHeight) :
        mapAreaSize(_mapAreaSize), worldMapWidth(_worldMapWidth), worldMapHeight(_worldMapHeight)
        {}

        // Core

        void GenerateWorldMap(UMap<int, UMap<int, SPtr<IMapGenerator>>> genAreas);
        Rect GetBounds();

        UPtr<MapArea>& GetArea(Point3 pos);

        // Basic data

        int mapAreaSize = -1;
        int worldMapWidth = -1;
        int worldMapHeight = -1;

        // Core world map data structures

        UMap<int, UMap<int, UMap<int, UPtr<MapArea>>>> areas;
    };

}  // namespace Forradia
