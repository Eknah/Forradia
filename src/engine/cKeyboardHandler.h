// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <SDL2/SDL_keycode.h>
#include <set>
#include "iKeyboardHandler.h"

namespace Forradia {

class cKeyboardHandler : public iKeyboardHandler {
 public:
  void ResetForNewFrame() const override;

  void DoKeyDown(SDL_Keycode key) const override;

  void DoKeyUp(SDL_Keycode key) const override;
};

}  // namespace Forradia
