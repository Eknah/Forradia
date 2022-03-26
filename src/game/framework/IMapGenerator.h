#pragma once
#include "../core/Aliases.h"
#include "../core/CPoint2.h"

namespace Forradia
{

class CEngine;
class CWorldMap;

class IMapGenerator
{

public:

    IMapGenerator(CEngine& engine, UPtr<CWorldMap>& worldMap) : Engine(engine), WorldMap(worldMap) {}

    // Core map area generation
    virtual void GenerateMapArea(CPoint2 worldMapCoord) = 0;


protected:
    CEngine& Engine;
    UPtr<CWorldMap>& WorldMap;

};

}
