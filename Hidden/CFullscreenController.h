#pragma once
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
        SDL_SetWindowFullscreen(Engine.GWindow, FullscreenOn ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    }

private:
    IEngine& Engine;
    bool FullscreenOn = True;
};

}
