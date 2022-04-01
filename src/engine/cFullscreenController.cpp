// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cFullscreenController.h"

namespace Forradia {

void cFullscreenController::UpdateFullscreenToggling() {
    if (Engine.KeyboardHandler.KeysBeenFired->count(SDLK_RETURN) > 0 &&
        Engine.KeyboardHandler.KeysBeingPressed->count(SDLK_LALT) > 0)
      ToggleFullscreen();
  }

void cFullscreenController::ToggleFullscreen() {
    FullscreenOn = !FullscreenOn;
    SDL_SetWindowFullscreen(Engine.Window.get(),
                            FullscreenOn ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
  }

}  // namespace Forradia
