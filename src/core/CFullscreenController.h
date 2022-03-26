#pragma once
#include "CommonExternal.h"
#include "IEngine.h"

namespace Forradia
{

class CFullscreenController
{

public:

    CFullscreenController(IEngine& engine) : Engine(engine) {}

    inline void ToggleFullscreen()
    {
        FullscreenOn = !FullscreenOn;
        SDL_SetWindowFullscreen(Engine.Window.get(), FullscreenOn ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
        SDL_SetWindowResizable(Engine.Window.get(), FullscreenOn ? SDL_FALSE : SDL_TRUE);
    }

private:

    IEngine& Engine;
    bool FullscreenOn = true;

};

}
