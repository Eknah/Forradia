// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include "../engine/cPoint2F.h"
#include "../engine/Aliases.h"

namespace Forradia {

class cMob {
 public:
  cMob(float X, float Y, std::string MobTypeName) : Position(X, Y),
      MobType(GetId(MobTypeName)) {}

  // Movement

  unsigned int TickLastMove = 0;
  int MoveSpeed = 30;
  float StepSize = 1.0f;
  float StepMultiplier = 0.1f;
  cPoint2F MoveDestination = {-1, -1};
  int MobType = 0;

  // Rotation

  float FacingAngle = 0.0f;

  // Localization

  cPoint2F Position = {-1, -1};
};

}  // namespace Forradia
