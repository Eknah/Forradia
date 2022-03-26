
#pragma once
#include "CommonExternal.h"

namespace Forradia
{

class F_Engine;

class F_GameLoop
{

public:

    F_GameLoop(F_Engine& engine) : Engine(engine) {}

    void Run();

private:

    // Looped functions
    void Update();
    void Render();

    // Resize event handling
    static int EventFilter(void* pthis, const SDL_Event* event);

    F_Engine& Engine;

};

}
