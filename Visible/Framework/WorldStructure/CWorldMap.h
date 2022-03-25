#pragma once
#include "CMapArea.h"
namespace Forradia
{

class IMapGenerator;

class CWorldMap
{

public:

    CWorldMap(int mapAreaSize) : MapAreaSize(mapAreaSize) {}

    // Core
    void GenerateWorldMap(IMapGenerator& mapGenerator);

    // Basic data
    int MapAreaSize = -1;

    // Core world map data structures
    List<UPtr<CMapArea>> MapAreas;
    UMap<int,UMap<int, int>> MapAreaCoords;

};

}
