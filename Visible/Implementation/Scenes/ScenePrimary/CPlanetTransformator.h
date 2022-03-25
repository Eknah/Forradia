#pragma once
namespace Forradia
{



class CPlanetTransformator
{
public:
    CPlanetTransformator(CEngine& engine) : Engine(engine) {}

    float GetNewY(float tiley, float mapx, float mapy);

private:
    CEngine& Engine;
};
}
