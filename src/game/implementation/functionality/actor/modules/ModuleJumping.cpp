// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ModuleJumping.h"
#include "../engine/Aliases.h"
#include "implementation/functionality/actor/Actor.h"
#include "implementation/functionality/actor/modules/ModuleMovementData.h"

namespace Forradia {

void cModuleJumping::ResetForNewFrame() {}

void cModuleJumping::Update() {
  if (isJumping) {
    auto DeltaTicks = Ticks() - tickStartJumping;
    auto JumpHeight =
        std::pow(((((-std::pow((((DeltaTicks - jumpDuration / 2.0f))), 2.0f) +
                     250000.0f)))) /
                     250000.0f,
                 3.0f) *
        maxJumpHeight;

    GetParentActor().GetModule<cModuleMovementData>().positionZ = JumpHeight;
  }

  if (Ticks() > tickStartJumping + jumpDuration) {
    GetParentActor().GetModule<cModuleMovementData>().positionZ = 0.0f;
    isJumping = false;
  }
}

void cModuleJumping::Jump() {
  isJumping = true;
  tickStartJumping = Ticks();
}

}  // namespace Forradia
