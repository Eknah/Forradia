// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "JumpingModule.h"
#include "Aliases.h"
#include "Actor.h"
#include "CoreMovmModule.h"

namespace Forradia
{

    void JumpingModule::ResetForNewFrame() {}

    void JumpingModule::Update()
    {
        auto& posz = GetParentActor().GetModule<CoreMovmModule>().positionZ;

        if (isJumping)
        {
            auto deltaTicks = timer.GetPassedTicks();
            auto jumpHeight = std::pow(((((-std::pow((((deltaTicks - jumpDuration / 2.0f))), 2.0f) + 250000.0f)))) / 250000.0f, 3.0f) * maxJumpHeight;

            posz = jumpHeight;
        }

        if (timer.HasFinished())
        {
            posz = 0.0f;
            isJumping = false;
        }
    }

    void JumpingModule::Jump()
    {
        if (isJumping) return;

        isJumping = true;
        timer.Reset();
    }

}  // namespace Forradia
