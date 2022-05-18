// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "Aliases.h"
#include "SDL_Deleter.h"

namespace Forradia
{
    typedef UPtrEx<SDL_Window, SDL_Deleter> WindowPtr;
    typedef UPtrEx<SDL_Surface, SDL_Deleter> SurfacePtr;
}