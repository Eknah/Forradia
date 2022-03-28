// Copyright (C) 2022  Andreas Åkerberg

#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class iKeyboardHandler
{

public:

    inline virtual void ResetForNewFrame() = 0;
    inline virtual void DoKeyDown(SDL_Keycode key) = 0;
    inline virtual void DoKeyUp(SDL_Keycode key) = 0;

    std::set<SDL_Keycode> KeysBeingPressed;
    std::set<SDL_Keycode> KeysBeenFired;

};

}
