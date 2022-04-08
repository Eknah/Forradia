// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Player.h"

namespace Forradia {

Player::Player(IEngine &e) : Actor(e, "Player") {
    AddModule<ModuleJumping>();
    AddModule<ModuleMovement>();
    AddModule<ModuleInventory>();
    AddModule<ModuleObjectUsage>();
  }

}  // namespace Forradia
