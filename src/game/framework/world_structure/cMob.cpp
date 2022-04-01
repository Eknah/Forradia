// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cMob.h"

namespace Forradia {

cMob::cMob(const iEngine &Engine, float X, float Y,
           std::string ModelName) :
    cActor(Engine, X, Y, ModelName) {
    AddIfNotExists<cModuleMovementData>();
}

}
