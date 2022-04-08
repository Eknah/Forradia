// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "FullscreenController.h"

namespace Forradia {

void FullscreenController::UpdateFullscreenToggling() {
    if (engine.keyboardHandler.keysBeenFired->count(SDLK_RETURN) > 0 &&
        engine.keyboardHandler.keysBeingPressed->count(SDLK_LALT) > 0)
      ToggleFullscreen();
  }

void FullscreenController::ToggleFullscreen() {
    fullscreenOn = !fullscreenOn;
    SDL_SetWindowFullscreen(engine.window.get(),
                            fullscreenOn ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
  }

}  // namespace Forradia
