
#pragma once
#include "CommonExternal.h"
#include "F_IKeyboardHandler.h"

namespace Forradia
{

class F_KeyboardHandler : public F_IKeyboardHandler
{

public:

    inline void ResetForNewFrame() override
    {
        KeysBeenFired.clear();
    }

    inline void DoKeyDown(SDL_Keycode key) override
    {
        KeysBeingPressed.insert(key);
        KeysBeenFired.insert(key);
    }

    inline void DoKeyUp(SDL_Keycode key) override
    {
        KeysBeingPressed.erase(key);
    }

};

}
