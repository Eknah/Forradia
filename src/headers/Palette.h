// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "SDL2/SDL_pixels.h"

namespace Forradia
{
    namespace Palette
    {
        const inline SDL_Color White = { 255, 255, 255, 255 };
        const inline SDL_Color WhiteSemiTrans = { 255, 255, 255, 150 };
        const inline SDL_Color Black = { 0, 0, 0, 255 };
        const inline SDL_Color MediumBlue = { 0, 150, 255, 255 };
        const inline SDL_Color MediumBlueSemiTrans = { 0, 150, 255, 100 };
        const inline SDL_Color Wheat = { 255, 255, 230, 255 };
        const inline SDL_Color LightMediumBlueSemiTrans = { 100, 200, 255, 100 };
        const inline SDL_Color Gray = { 100, 100, 100, 255 };
        const inline SDL_Color LightGray = { 150, 150, 150, 255 };
        const inline SDL_Color DarkGray = { 50, 50, 50, 255 };
    };
}