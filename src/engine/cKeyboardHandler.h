// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <set>
#include "iKeyboardHandler.h"

namespace Forradia {

class cKeyboardHandler : public iKeyboardHandler {
 public:
  inline void ResetForNewFrame() const override {
      KeysBeenFired->clear();
  }

  inline void DoKeyDown(SDL_Keycode key) const override {
    KeysBeingPressed->insert(key);
    KeysBeenFired->insert(key);
  }

  inline void DoKeyUp(SDL_Keycode key) const override {
      KeysBeingPressed->erase(key);
  }
};

}  // namespace Forradia
