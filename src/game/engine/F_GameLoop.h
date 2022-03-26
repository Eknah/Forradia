
#pragma once
#include "../core/F_IGameLoop.h"

namespace Forradia
{

class F_Engine;

class F_GameLoop : public F_IGameLoop
{

public:

    F_GameLoop(F_Engine& engine) : F_IGameLoop(engine) {}

    void Run() override;

private:

    // Looped functions
    void Update() override;
    void Render() override;

    // Resize event handling
    static int EventFilter(void* pthis, const SDL_Event* event);

};

}
