#pragma once
#include "../core/Aliases.h"
#include "../core/F_Point2.h"

namespace Forradia
{

class F_Engine;
class F_WorldMap;

class F_IMapGenerator
{

public:

    F_IMapGenerator(F_Engine& engine, UPtr<F_WorldMap>& worldMap) : Engine(engine), WorldMap(worldMap) {}

    // Core map area generation
    virtual void GenerateMapArea(F_Point2 worldMapCoord) = 0;


protected:
    F_Engine& Engine;
    UPtr<F_WorldMap>& WorldMap;

};

}
