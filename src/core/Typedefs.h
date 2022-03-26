#pragma once
#include "CommonExternal.h"
#include "../core/CSDL_Deleter.h"
#include "../core/Aliases.h"

namespace Forradia
{

typedef UPtrEx<SDL_Window, CSDL_Deleter> WindowPtr;
typedef UPtrEx<SDL_Surface, CSDL_Deleter> SurfacePtr;

}
