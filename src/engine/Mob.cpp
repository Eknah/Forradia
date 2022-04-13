// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Mob.h"
#include "implementation/functionality/actor/modules/CoreMovementModule.h"
#include "implementation/functionality/actor/modules/MobAIMovementModule.h"

namespace Forradia {

Mob::Mob(const IEngine &e, float x, float y,
           std::string modelName) :
    Actor(e, x, y, modelName) {
    AddIfNotExists<MobAIMovementModule>();
}

}
