
#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class F_Engine;

    class F_IGameLoop
    {

    public:

        F_IGameLoop(F_Engine& engine) : Engine(engine) {}

        virtual void Run() = 0;

        // Looped functions
        virtual void Update() = 0;
        virtual void Render() = 0;

    protected:

        F_Engine& Engine;

    };

}
