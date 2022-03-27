
#pragma once
#include "cMapArea.h"

namespace Forradia
{

class iMapGenerator;

class cWorldMap
{

public:

    cWorldMap(int mapAreaSize) : MapAreaSize(mapAreaSize) {}

    // Core
    void GenerateWorldMap(iMapGenerator& mapGenerator);

    // Basic data
    int MapAreaSize = -1;

    // Core world map data structures
    UMap<int,UMap<int,UMap<int, UPtr<cMapArea>>>> MapAreas;

};

}
