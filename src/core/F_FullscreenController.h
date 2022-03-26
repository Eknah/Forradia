
#pragma once
#include "F_IEngine.h"
#include "F_IFullscreenController.h"

namespace Forradia
{

class F_FullscreenController : public F_IFullscreenController
{

public:

    F_FullscreenController(F_IEngine& engine) : F_IFullscreenController(engine) {}

    inline void UpdateFullscreenToggling() override
    {
        if (Engine.KeyboardHandler.KeysBeenFired.count(SDLK_RETURN) > 0 && Engine.KeyboardHandler.KeysBeingPressed.count(SDLK_LALT) > 0)
            ToggleFullscreen();
    }

    inline void ToggleFullscreen() override
    {
        FullscreenOn = !FullscreenOn;
        SDL_SetWindowFullscreen(Engine.Window.get(), FullscreenOn ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    }

};

}
