// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <SDL2/SDL_keycode.h>
#include <set>
#include "Aliases.h"

namespace Forradia {

class IKeyboardHandler {
 public:
  virtual void ResetForNewFrame() const = 0;
  virtual void DoKeyDown(SDL_Keycode key) const = 0;
  virtual void DoKeyUp(SDL_Keycode key) const = 0;

  const UPtr<std::set<SDL_Keycode>> keysBeingPressed
  = MakeUPtr<std::set<SDL_Keycode>>();

  const UPtr<std::set<SDL_Keycode>> keysBeenFired
  = MakeUPtr<std::set<SDL_Keycode>>();
};

}  // namespace Forradia
