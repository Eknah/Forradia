// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/iModule.h"
#include "../engine/Aliases.h"
#include "../engine/cPoint2F.h"
#include "../engine/cPoint3.h"

namespace Forradia {

class cModuleMovementData : public iModule {
 public:
  using iModule::iModule;

  void ResetForNewFrame() override;
  void Update() override {};

  cPoint3 WorldMapCoord = {1, 1, 0};
  cPoint2F Position = {50.0f, 50.0f};
  float PositionZ = 0.0f;
  UPtr<float> FacingAngle = MakeUPtr<float>(0.0f);

  cPoint2F MoveDestination = {-1, -1};
  unsigned int TickLastMove = 0;
  int MoveSpeed = 30;
  float StepSize = 3.0f;
  float StepMultiplier = 0.1f;
  bool IsWalking = false;

};

}  // namespace Forradia
