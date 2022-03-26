#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class F_Engine;

class F_MobsEngine
{

public:

    F_MobsEngine(F_Engine& engine) : Engine(engine) {}

    void Update();

private:

    F_Engine& Engine;

};

}
