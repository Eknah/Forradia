// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"
#include "../engine/iModule.h"

namespace Forradia {

class cObject;

class cModuleObjectUsage : public iModule {
 public:
  using iModule::iModule;

  void ResetForNewFrame() override;
  void Update() override;

  SPtr<cObject> ObjectBeingUsed = nullptr;
};

}  // namespace Forradia
