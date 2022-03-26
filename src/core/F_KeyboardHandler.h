
#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class F_KeyboardHandler
{

public:

    inline void ResetForNewFrame()
    {
        KeysBeenFired.clear();
    }

    inline void DoKeyDown(SDL_Keycode key)
    {
        KeysBeingPressed.insert(key);
        KeysBeenFired.insert(key);
    }

    inline void DoKeyUp(SDL_Keycode key)
    {
        KeysBeingPressed.erase(key);
    }

    std::set<SDL_Keycode> KeysBeingPressed;
    std::set<SDL_Keycode> KeysBeenFired;

};

}
