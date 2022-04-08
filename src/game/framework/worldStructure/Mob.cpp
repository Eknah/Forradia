// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Mob.h"

namespace Forradia {

cMob::cMob(const iEngine &engine, float x, float y,
           std::string modelName) :
    cActor(engine, x, y, modelName) {
    AddIfNotExists<cModuleMovementData>();
    GetModule<cModuleMovementData>().isWalking = true;
}

}
