
#pragma once
#include "CommonExternal.h"
#include "F_IEngine.h"

namespace Forradia
{

class F_FullscreenController
{

public:

    F_FullscreenController(F_IEngine& engine) : Engine(engine) {}

    inline void UpdateFullscreenToggling()
    {
        if (Engine.KeyboardHandler.KeysBeenFired.count(SDLK_RETURN) > 0 && Engine.KeyboardHandler.KeysBeingPressed.count(SDLK_LALT) > 0)
            ToggleFullscreen();
    }

    inline void ToggleFullscreen()
    {
        FullscreenOn = !FullscreenOn;
        SDL_SetWindowFullscreen(Engine.Window.get(), FullscreenOn ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    }

private:

    F_IEngine& Engine;
    bool FullscreenOn = true;

};

}
