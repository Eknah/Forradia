// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include "../engine/Point2F.h"
#include "../engine/Aliases.h"
#include "implementation/functionality/actor/Actor.h"
#include "implementation/functionality/actor/modules/ModuleMovementData.h"

namespace Forradia {

class iEngine;

class cMob : public cActor {
 public:
  cMob(const iEngine &engine, float x, float y,
       std::string modelName);
};

}  // namespace Forradia
