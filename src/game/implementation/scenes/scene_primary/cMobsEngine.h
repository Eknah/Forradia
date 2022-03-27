
#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class cEngine;

class cMobsEngine
{

public:

    cMobsEngine(cEngine& engine) : Engine(engine) {}

    void Update();

private:

    cEngine& Engine;

};

}
