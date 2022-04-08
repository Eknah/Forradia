// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "implementation/functionality/actor/Actor.h"
#include "implementation/functionality/actor/modules/ModuleInventory.h"
#include "implementation/functionality/actor/modules/ModuleJumping.h"
#include "implementation/functionality/actor/modules/ModuleMovement.h"
#include "implementation/functionality/actor/modules/ModuleObjectUsage.h"

namespace Forradia {

class Player : public Actor {
 public:
  explicit Player(IEngine &e);
};

}  // namespace Forradia
