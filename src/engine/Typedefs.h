// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"
#include "../engine/cSDL_Deleter.h"

namespace Forradia {

typedef UPtrEx<SDL_Window, cSDL_Deleter> WindowPtr;
typedef UPtrEx<SDL_Surface, cSDL_Deleter> SurfacePtr;

}  // namespace Forradia
