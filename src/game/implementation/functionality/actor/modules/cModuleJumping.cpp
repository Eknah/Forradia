// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cModuleJumping.h"
#include "../engine/Aliases.h"
#include "implementation/functionality/actor/cActor.h"
#include "implementation/functionality/actor/modules/cModuleMovementData.h"

namespace Forradia {

void cModuleJumping::ResetForNewFrame() {}

void cModuleJumping::Update() {
  if (IsJumping) {
    auto DeltaTicks = Ticks() - TickStartJumping;
    auto JumpHeight =
        std::pow(((((-std::pow((((DeltaTicks - JumpDuration / 2.0f))), 2.0f) +
                     250000.0f)))) /
                     250000.0f,
                 3.0f) *
        MaxJumpHeight;

    GetParentActor().GetModule<cModuleMovementData>().PositionZ = JumpHeight;
  }

  if (Ticks() > TickStartJumping + JumpDuration) {
    GetParentActor().GetModule<cModuleMovementData>().PositionZ = 0.0f;
    IsJumping = false;
  }
}

void cModuleJumping::Jump() {
  IsJumping = true;
  TickStartJumping = Ticks();
}

}  // namespace Forradia
