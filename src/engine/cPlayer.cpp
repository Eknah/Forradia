// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cPlayer.h"

namespace Forradia {

cPlayer::cPlayer(iEngine &engine) : cActor(engine, "Player") {
    AddModule<cModuleJumping>();
    AddModule<cModuleMovement>();
    AddModule<cModuleInventory>();
    AddModule<cModuleObjectUsage>();
  }

}  // namespace Forradia
