// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "SDL2/SDL_pixels.h"

namespace Forradia
{

    class Palette
    {
    public:
        SDL_Color white = { 255, 255, 255, 255 };
        SDL_Color whiteSemiTrans = { 255, 255, 255, 150 };
        SDL_Color black = { 0, 0, 0, 255 };
        SDL_Color mediumBlue = { 0, 150, 255, 255 };
        SDL_Color mediumBlueSemiTrans = { 0, 150, 255, 100 };
        SDL_Color wheat = { 255, 255, 230, 255 };
    };

}  // namespace Forradia
