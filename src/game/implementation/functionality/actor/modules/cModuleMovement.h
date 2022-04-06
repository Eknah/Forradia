// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cPoint2F.h"
#include "../engine/iModule.h"

namespace Forradia {

class cModuleMovement : public iModule {
 public:
  class MovementInstruction {
   public:
    bool TryMoveForward = false;
    bool TryMoveRight = false;
    bool TryMoveBack = false;
    bool TryMoveLeft = false;
  };

  cModuleMovement(const iEngine &Engine_, cActor *ParentActor_);

  //using iModule::iModule;

  void ResetForNewFrame() override;
  void Update() override;

  void UpdateRotation(float newFacingAngle);

  MovementInstruction Instruction;

  float FacingAngleRotated = 0.0f;

 private:
  void UpdateDirectionalMovement();
  void UpdateDestinationMovement();

};

}  // namespace Forradia
