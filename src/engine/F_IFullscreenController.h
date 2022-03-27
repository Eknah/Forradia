
#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class F_IEngine;

class F_IFullscreenController
{

public:

    F_IFullscreenController(F_IEngine& engine) : Engine(engine) {}

    inline virtual void UpdateFullscreenToggling() = 0;
    inline virtual void ToggleFullscreen() = 0;

protected:

    F_IEngine& Engine;
    bool FullscreenOn = true;

};

}
