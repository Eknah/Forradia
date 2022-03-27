
#include "F_ModuleJumping.h"
#include "CommonExternal.h"
#include "../engine/Aliases.h"

namespace Forradia
{

void F_ModuleJumping::ResetForNewFrame()
{}

void F_ModuleJumping::Update()
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

void F_ModuleJumping::Jump()
{

        IsJumping = true;
        TickStartJumping = Ticks();
}

}
