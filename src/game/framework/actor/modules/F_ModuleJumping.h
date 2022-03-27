
#pragma once
#include "F_IModule.h"

namespace Forradia
{

class F_ModuleJumping : public F_IModule
{

public:

    using F_IModule::F_IModule;

    void ResetForNewFrame() override;
    void Update() override;
    void Jump();

    float PositionZ = 0.0f;

private:

    bool IsJumping = false;
    int JumpDuration = 600;
    unsigned int TickStartJumping = 0;
    float MaxJumpHeight = 1.0f;

};

}
