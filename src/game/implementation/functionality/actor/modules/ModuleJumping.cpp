// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ModuleJumping.h"
#include "../engine/Aliases.h"
#include "implementation/functionality/actor/Actor.h"
#include "implementation/functionality/actor/modules/ModuleMovementData.h"

namespace Forradia {

void ModuleJumping::ResetForNewFrame() {}

void ModuleJumping::Update() {
  if (isJumping) {
    auto deltaTicks = Ticks() - tickStartJumping;
    auto jumpHeight =
        std::pow(((((-std::pow((((deltaTicks - jumpDuration / 2.0f))), 2.0f) +
                     250000.0f)))) /
                     250000.0f,
                 3.0f) *
        maxJumpHeight;

    GetParentActor().GetModule<ModuleMovementData>().positionZ = jumpHeight;
  }

  if (Ticks() > tickStartJumping + jumpDuration) {
    GetParentActor().GetModule<ModuleMovementData>().positionZ = 0.0f;
    isJumping = false;
  }
}

void ModuleJumping::Jump() {
  isJumping = true;
  tickStartJumping = Ticks();
}

}  // namespace Forradia
