// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "iEngine.h"
#include "iFullscreenController.h"

namespace Forradia
{

class cFullscreenController : public iFullscreenController
{

public:

    cFullscreenController(iEngine& engine) : iFullscreenController(engine) {}

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
