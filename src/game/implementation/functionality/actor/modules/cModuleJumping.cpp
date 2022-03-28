// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cModuleJumping.h"
#include "../engine/Aliases.h"
#include "CommonExternal.h"

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

    PositionZ = JumpHeight;
  }

  if (Ticks() > TickStartJumping + JumpDuration) {
    PositionZ = 0.0f;
    IsJumping = false;
  }
}

void cModuleJumping::Jump() {

  IsJumping = true;
  TickStartJumping = Ticks();
}

}  // namespace Forradia
