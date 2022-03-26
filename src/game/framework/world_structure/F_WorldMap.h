#pragma once
#include "F_MapArea.h"

namespace Forradia
{

class F_IMapGenerator;

class F_WorldMap
{

public:

    F_WorldMap(int mapAreaSize) : MapAreaSize(mapAreaSize) {}

    // Core
    void GenerateWorldMap(F_IMapGenerator& mapGenerator);

    // Basic data
    int MapAreaSize = -1;

    // Core world map data structures
    std::vector<UPtr<F_MapArea>> MapAreas;
    UMap<int,UMap<int, int>> MapAreaCoords;

};

}
