#pragma once
namespace Forradia
{

class CEngine;

class CMobsEngine
{

public:
    CMobsEngine(CEngine& engine) : Engine(engine) {}

    void Update();

private:
    CEngine& Engine;

};

}
