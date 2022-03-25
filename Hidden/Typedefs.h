#pragma once
#include "CommonExternal.h"
#include "../Hidden/CSDL_Deleter.h"
#include "../Hidden/Aliases.h"
namespace Forradia
{

typedef UPtrEx<SDL_Renderer, CSDL_Deleter> RendererPtr;
typedef UPtrEx<SDL_Window, CSDL_Deleter> WindowPtr;
typedef UPtrEx<SDL_Surface, CSDL_Deleter> SurfacePtr;
typedef UPtrEx<SDL_Texture, CSDL_Deleter> ImagePtr;

}
