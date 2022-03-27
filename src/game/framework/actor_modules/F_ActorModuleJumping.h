
#pragma once
#include "F_IActorModule.h"

namespace Forradia
{

class F_ActorModuleJumping : public F_IActorModule
{

public:

    using F_IActorModule::F_IActorModule;

    void ResetForNewFrame() override;
    void Update() override;
    void Jump();

    float PositionZ = 0.0f;

private:

    bool IsJumping = false;
    int JumpDuration = 600;
    int TickStartJumping = 0;
    float MaxJumpHeight = 1.0f;

};

}
