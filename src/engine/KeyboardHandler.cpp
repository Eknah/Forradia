// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "KeyboardHandler.h"

namespace Forradia {

void KeyboardHandler::ResetForNewFrame() const {
      keysBeenFired->clear();
  }

void KeyboardHandler::DoKeyDown(SDL_Keycode key) const {
    keysBeingPressed->insert(key);
    keysBeenFired->insert(key);
  }

void KeyboardHandler::DoKeyUp(SDL_Keycode key) const {
      keysBeingPressed->erase(key);
  }

}  // namespace Forradia
