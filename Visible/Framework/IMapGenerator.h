#pragma once

namespace Forradia
{

class CEngine;
class CWorldMap;

class IMapGenerator
{
public:
    IMapGenerator(CEngine& engine, UPtr<CWorldMap>& worldMap) : Engine(engine), WorldMap(worldMap) {}

    virtual void GenerateMapArea(CPoint2 worldMapCoord) = 0;

protected:
    CEngine& Engine;
    UPtr<CWorldMap>& WorldMap;

};

}
