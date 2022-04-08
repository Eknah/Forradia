// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Mob.h"

namespace Forradia {

Mob::Mob(const IEngine &engine, float x, float y,
           std::string modelName) :
    Actor(engine, x, y, modelName) {
    AddIfNotExists<ModuleMovementData>();
    GetModule<ModuleMovementData>().isWalking = true;
}

}
