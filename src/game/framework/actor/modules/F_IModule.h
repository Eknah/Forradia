
#pragma once

namespace Forradia
{

class F_IEngine;
class F_Actor;

class F_IModule
{

public:

    F_IModule(F_IEngine& Engine_, F_Actor& ParentActor_) : Engine(Engine_), ParentActor(ParentActor_) {}

    virtual void ResetForNewFrame() = 0;
    virtual void Update() = 0;

protected:

    F_IEngine& Engine;
    F_Actor& ParentActor;

};

}
