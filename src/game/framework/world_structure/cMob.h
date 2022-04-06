// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include "../engine/cPoint2F.h"
#include "../engine/Aliases.h"
#include "implementation/functionality/actor/cActor.h"
#include "implementation/functionality/actor/modules/cModuleMovementData.h"

namespace Forradia {

class iEngine;

class cMob : public cActor {
 public:
  cMob(const iEngine &engine, float X, float Y,
       std::string modelName);
};

}  // namespace Forradia
