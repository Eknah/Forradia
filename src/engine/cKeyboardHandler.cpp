// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cKeyboardHandler.h"

namespace Forradia {

void cKeyboardHandler::ResetForNewFrame() const {
      KeysBeenFired->clear();
  }

void cKeyboardHandler::DoKeyDown(SDL_Keycode key) const {
    KeysBeingPressed->insert(key);
    KeysBeenFired->insert(key);
  }

void cKeyboardHandler::DoKeyUp(SDL_Keycode key) const {
      KeysBeingPressed->erase(key);
  }

}  // namespace Forradia
