
#include "F_ActorModuleJumping.h"
#include "CommonExternal.h"
#include "../core/Aliases.h"

namespace Forradia
{

void F_ActorModuleJumping::ResetForNewFrame()
{}

void F_ActorModuleJumping::Update()
{
    if (IsJumping)
    {
        auto DeltaTicks = Ticks() - TickStartJumping;
        auto JumpHeight = std::pow((-std::pow((DeltaTicks - JumpDuration / 2.0f), 2.0f) + 250000.0f) / 250000.0f, 3.0f) * MaxJumpHeight;
        PositionZ = JumpHeight;
    }

    if (Ticks() > TickStartJumping + JumpDuration)
    {
        PositionZ = 0.0f;
        IsJumping = false;
    }
}

void F_ActorModuleJumping::Jump()
{

        IsJumping = true;
        TickStartJumping = Ticks();
}

}
