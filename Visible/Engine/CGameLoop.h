#pragma once

namespace Forradia
{

class CEngine;

class CGameLoop
{

public:

    CGameLoop(CEngine& engine) : Engine(engine) {}

    void Run();

private:

    // Looped functions
    void Update();
    void Render();

    // Resize event handling
    static int EventFilter(void* pthis, const SDL_Event* event);

    CEngine& Engine;

};

}
