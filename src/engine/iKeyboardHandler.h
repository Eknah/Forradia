// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <SDL2/SDL_keycode.h>
#include <set>
#include "Aliases.h"

namespace Forradia {

class iKeyboardHandler {
 public:
  inline virtual void ResetForNewFrame() const = 0;
  inline virtual void DoKeyDown(SDL_Keycode key) const = 0;
  inline virtual void DoKeyUp(SDL_Keycode key) const = 0;

  const UPtr<std::set<SDL_Keycode>> KeysBeingPressed
  = MakeUPtr<std::set<SDL_Keycode>>();

  const UPtr<std::set<SDL_Keycode>> KeysBeenFired
  = MakeUPtr<std::set<SDL_Keycode>>();
};

}  // namespace Forradia
