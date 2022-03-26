
#pragma once
#include "CommonExternal.h"
#include "../core/F_SDL_Deleter.h"
#include "../core/Aliases.h"

namespace Forradia
{

typedef UPtrEx<SDL_Window, F_SDL_Deleter>   F_WindowPtr;
typedef UPtrEx<SDL_Surface, F_SDL_Deleter>  F_SurfacePtr;

}
