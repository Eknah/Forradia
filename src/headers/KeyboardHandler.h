// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <SDL2/SDL_keycode.h>
#include <set>
#include "IKeyboardHandler.h"

namespace Forradia
{
    class KeyboardHandler : public IKeyboardHandler
    {
    public:
        void ResetForNewFrame() const override;
        void KeyDown(SDL_Keycode key) const override;
        void KeyUp(SDL_Keycode key) const override;
    };
}