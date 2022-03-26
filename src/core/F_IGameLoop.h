
#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class F_IEngine;

    class F_IGameLoop
    {

    public:

        F_IGameLoop(F_IEngine& engine) : Engine(engine) {}

        inline virtual void Run() = 0;

        // Looped functions
        inline virtual void Update() = 0;
        inline virtual void Render() = 0;

    protected:

        F_IEngine& Engine;

    };

}
