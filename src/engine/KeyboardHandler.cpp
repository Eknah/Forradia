// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "KeyboardHandler.h"

namespace Forradia {

void cKeyboardHandler::ResetForNewFrame() const {
      keysBeenFired->clear();
  }

void cKeyboardHandler::DoKeyDown(SDL_Keycode key) const {
    keysBeingPressed->insert(key);
    keysBeenFired->insert(key);
  }

void cKeyboardHandler::DoKeyUp(SDL_Keycode key) const {
      keysBeingPressed->erase(key);
  }

}  // namespace Forradia
