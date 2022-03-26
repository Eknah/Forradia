
#include "F_ActorModuleJumping.h"
#include "CommonExternal.h"
#include "../core/Aliases.h"

namespace Forradia
{

void F_ActorModuleJumping::Update()
{
    if (IsJumping)
    {
        auto delta_ticks = Ticks() - TickStartJumping;
        auto jump_height = std::pow((-std::pow((delta_ticks - JumpDuration / 2.0f), 2.0f) + 250000.0f) / 250000.0f, 3.0f) * MaxJumpHeight;
        PositionZ = jump_height;
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
