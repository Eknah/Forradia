
#pragma once

namespace Forradia
{

class iEngine;
class cActor;

class iModule
{

public:

    iModule(iEngine& Engine_, cActor& ParentActor_) : Engine(Engine_), ParentActor(ParentActor_) {}

    virtual void ResetForNewFrame() = 0;
    virtual void Update() = 0;

protected:

    iEngine& Engine;
    cActor& ParentActor;

};

}
