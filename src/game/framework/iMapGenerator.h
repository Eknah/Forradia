
#pragma once
#include "../engine/Aliases.h"

namespace Forradia
{

class cEngine;
class cWorldMap;

class iMapGenerator
{

public:

    iMapGenerator(cEngine& engine, UPtr<cWorldMap>& worldMap) : Engine(engine), WorldMap(worldMap) {}

    // Core map area generation
    virtual void GenerateMapArea(int WorldX, int WorldY, int WorldZ) = 0;


protected:
    cEngine& Engine;
    UPtr<cWorldMap>& WorldMap;

};

}
