// Copyright (C) 2022  Andreas Åkerberg

#pragma once
#include "CommonExternal.h"
#include "../engine/cSDL_Deleter.h"
#include "../engine/Aliases.h"

namespace Forradia
{

typedef UPtrEx<SDL_Window, cSDL_Deleter>   F_WindowPtr;
typedef UPtrEx<SDL_Surface, cSDL_Deleter>  F_SurfacePtr;

}
