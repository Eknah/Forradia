// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace Forradia
{

    class SDL_Deleter
    {
    public:
        void operator()(SDL_Window* p) const;
        void operator()(SDL_Renderer* p) const;
        void operator()(SDL_Texture* p) const;
        void operator()(SDL_Surface* p) const;
        void operator()(TTF_Font* p) const;
    };

}  // namespace Forradia
