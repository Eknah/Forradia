// Copyright (C) 2022  Andreas Åkerberg

#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class iEngine;

    class iGameLoop
    {

    public:

        iGameLoop(iEngine& engine) : Engine(engine) {}

        inline virtual void Run() = 0;

        // Looped functions
        inline virtual void Update() = 0;
        inline virtual void Render() = 0;

    protected:

        iEngine& Engine;

    };

}
