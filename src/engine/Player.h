// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "implementation/functionality/actor/Actor.h"
#include "../engine/InventoryModule.h"
#include "implementation/functionality/actor/modules/JumpingModule.h"
#include "implementation/functionality/actor/modules/DestMovementModule.h"
#include "implementation/functionality/actor/modules/DirectionMovementModule.h"
#include "implementation/functionality/actor/modules/ObjectUsageModule.h"

namespace Forradia {

class Player : public Actor {
 public:
  explicit Player(IEngine &e);
};

}  // namespace Forradia
