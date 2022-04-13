// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "JumpingModule.h"
#include "../engine/Aliases.h"
#include "implementation/functionality/actor/Actor.h"
#include "implementation/functionality/actor/modules/MovementDataModule.h"

namespace Forradia
{

    void JumpingModule::ResetForNewFrame() {}

    void JumpingModule::Update()
    {
        if (isJumping)
        {
            auto deltaTicks = Ticks() - tickStartJumping;
            auto jumpHeight =
                std::pow(((((-std::pow((((deltaTicks - jumpDuration / 2.0f))), 2.0f) +
                    250000.0f)))) /
                    250000.0f,
                    3.0f) *
                maxJumpHeight;

            GetParentActor().GetModule<CoreMovementModule>().positionZ = jumpHeight;
        }

        if (Ticks() > tickStartJumping + jumpDuration)
        {
            GetParentActor().GetModule<CoreMovementModule>().positionZ = 0.0f;
            isJumping = false;
        }
    }

    void JumpingModule::Jump()
    {
        isJumping = true;
        tickStartJumping = Ticks();
    }

}  // namespace Forradia
