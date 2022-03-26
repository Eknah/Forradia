#pragma once
#include "CommonExternal.h"
#include "../hidden/CSDL_Deleter.h"
#include "../hidden/Aliases.h"

namespace Forradia
{

typedef UPtrEx<SDL_Window, CSDL_Deleter> WindowPtr;
typedef UPtrEx<SDL_Surface, CSDL_Deleter> SurfacePtr;

}