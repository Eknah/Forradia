// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/iModule.h"

namespace Forradia {

class cModuleJumping : public iModule {
 public:
  using iModule::iModule;

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

} // namespace Forradia
