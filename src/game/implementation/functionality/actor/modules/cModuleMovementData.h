// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/iModule.h"
#include "../engine/Aliases.h"
#include "../engine/Point2F.h"
#include "../engine/Point3.h"

namespace Forradia {

class cModuleMovementData : public iModule {
 public:
  using iModule::iModule;

  void ResetForNewFrame() override;
  void Update() override {};

  cPoint3 worldMapCoord = {1, 1, 0};
  cPoint2F position = {50.0f, 50.0f};
  float positionZ = 0.0f;
  UPtr<float> facingAngle = MakeUPtr<float>(0.0f);

  cPoint2F moveDestination = {-1, -1};
  unsigned int tickLastMove = 0;
  int moveSpeed = 30;
  float stepSize = 3.0f;
  float stepMultiplier = 0.1f;
  bool isWalking = false;

};

}  // namespace Forradia
