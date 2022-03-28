// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "SDL2/SDL_pixels.h"

namespace Forradia {

class cPalette {
 public:
  SDL_Color White = {255, 255, 255, 255};
  SDL_Color WhiteSemiTrans = {255, 255, 255, 150};
  SDL_Color Black = {0, 0, 0, 255};
  SDL_Color MediumBlue = {0, 150, 255, 255};
  SDL_Color MediumBlueSemiTrans = {0, 150, 255, 100};
  SDL_Color Wheat = {255, 255, 230, 255};
};

} // namespace Forradia
