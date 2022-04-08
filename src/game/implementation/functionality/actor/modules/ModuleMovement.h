// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Point2F.h"
#include "../engine/IModule.h"

namespace Forradia {

class ModuleMovement : public IModule {
 public:
  class MovementInstruction {
   public:
    bool tryMoveForward = false;
    bool tryMoveRight = false;
    bool tryMoveBack = false;
    bool tryMoveLeft = false;
  };

  ModuleMovement(const IEngine &_engine, Actor *_parentActor);

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
