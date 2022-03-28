// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"
#include "../engine/cSDL_Deleter.h"
#include "CommonExternal.h"

namespace Forradia {

typedef UPtrEx<SDL_Window, cSDL_Deleter> F_WindowPtr;
typedef UPtrEx<SDL_Surface, cSDL_Deleter> F_SurfacePtr;

}  // namespace Forradia
