// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/iModule.h"
#include "framework/world_structure/cObject.h"

namespace Forradia {

class cModuleObjectUsage : public iModule {

public:
  using iModule::iModule;

  void ResetForNewFrame() override;
  void Update() override;

  SPtr<cObject> ObjectBeingUsed = nullptr;
};

} // namespace Forradia
