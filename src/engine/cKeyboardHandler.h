// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "CommonExternal.h"
#include "iKeyboardHandler.h"

namespace Forradia {

class cKeyboardHandler : public iKeyboardHandler {

public:
  inline void ResetForNewFrame() override { KeysBeenFired.clear(); }

  inline void DoKeyDown(SDL_Keycode key) override {
    KeysBeingPressed.insert(key);
    KeysBeenFired.insert(key);
  }

  inline void DoKeyUp(SDL_Keycode key) override { KeysBeingPressed.erase(key); }
};

} // namespace Forradia
