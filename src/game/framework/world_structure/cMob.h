// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include "../engine/cPoint2F.h"
#include "../engine/Aliases.h"
#include "implementation/functionality/actor/cActor.h"

namespace Forradia {

class iEngine;

class cMob : public cActor {
 public:
  cMob(const iEngine &Engine, float X, float Y, std::string ModelName) :
      cActor(Engine, X, Y, ModelName) {}

  // Movement

  unsigned int TickLastMove = 0;
  int MoveSpeed = 30;
  float StepSize = 1.0f;
  float StepMultiplier = 0.1f;
  cPoint2F MoveDestination = {-1, -1};

  // Rotation

  float FacingAngle = 0.0f;

  // Localization

  //cPoint2F Position = {-1, -1};
};

}  // namespace Forradia
