// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <set>
#include "CommonExternal.h"

namespace Forradia {

class iKeyboardHandler {
 public:
  inline virtual void ResetForNewFrame() = 0;
  inline virtual void DoKeyDown(SDL_Keycode key) = 0;
  inline virtual void DoKeyUp(SDL_Keycode key) = 0;

  std::set<SDL_Keycode> KeysBeingPressed;
  std::set<SDL_Keycode> KeysBeenFired;
};

}  // namespace Forradia
