#pragma once
#include "SDL2/SDL.h"

namespace Forradia
{

class CEngine;

class CSceneBase
{

public:

    CSceneBase(CEngine& engine) : Engine(engine) {}

    // To implement in child
    virtual void Enter() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void DoMouseDown(Uint8 mouseButton) = 0;
    virtual void DoMouseUp(Uint8 mouseButton) = 0;

protected:

    CEngine& Engine;

};

}
