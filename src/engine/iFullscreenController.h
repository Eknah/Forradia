// Copyright (C) 2022  Andreas Åkerberg

#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class iEngine;

class iFullscreenController
{

public:

    iFullscreenController(iEngine& engine) : Engine(engine) {}

    inline virtual void UpdateFullscreenToggling() = 0;
    inline virtual void ToggleFullscreen() = 0;

protected:

    iEngine& Engine;
    bool FullscreenOn = true;

};

}
