
#pragma once
#include "../engine/cMapArea.h"

namespace Forradia
{

class iMapGenerator;

class cWorldMap
{

public:

    cWorldMap(int MapAreaSize_) : MapAreaSize(MapAreaSize_) {}

    // Core
    void GenerateWorldMap(iMapGenerator& MapGenerator);

    // Basic data
    int MapAreaSize = -1;

    // Core world map data structures
    UMap<int,UMap<int,UMap<int, UPtr<cMapArea>>>> MapAreas;

};

}
