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
    bool tryMoveForward = false;
    bool tryMoveRight = false;
    bool tryMoveBack = false;
    bool tryMoveLeft = false;
  };

  cModuleMovement(const iEngine &_engine, cActor *_parentActor);

  //using iModule::iModule;

  void ResetForNewFrame() override;
  void Update() override;

  void UpdateRotation(float newFacingAngle);

  MovementInstruction instruction;

  float facingAngleRotated = 0.0f;

 private:
  void UpdateDirectionalMovement();
  void UpdateDestinationMovement();

};

}  // namespace Forradia
