// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cSDL_Deleter.h"

namespace Forradia {

void cSDL_Deleter::operator()(SDL_Window *p) const {
    SDL_DestroyWindow(p);
}

void cSDL_Deleter::operator()(SDL_Renderer *p) const {
    SDL_DestroyRenderer(p);
}

void cSDL_Deleter::operator()(SDL_Texture *p) const {
    SDL_DestroyTexture(p);
}

void cSDL_Deleter::operator()(SDL_Surface *p) const {
    SDL_FreeSurface(p);
}

void cSDL_Deleter::operator()(TTF_Font *p) const {
    TTF_CloseFont(p);
}

}  // namespace Forradia
