
#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class cEngine;

class cMobsEngine
{

public:

    cMobsEngine(cEngine& Engine_) : Engine(Engine_) {}

    void Update();

private:

    cEngine& Engine;

};

}
