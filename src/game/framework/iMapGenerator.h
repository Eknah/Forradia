
#pragma once
#include "../engine/Aliases.h"
#include "../engine/cPoint2.h"

namespace Forradia
{

class cEngine;
class cWorldMap;

class iMapGenerator
{

public:

    iMapGenerator(cEngine& engine, UPtr<cWorldMap>& worldMap) : Engine(engine), WorldMap(worldMap) {}

    // Core map area generation
    virtual void GenerateMapArea(cPoint2 worldMapCoord) = 0;


protected:
    cEngine& Engine;
    UPtr<cWorldMap>& WorldMap;

};

}
