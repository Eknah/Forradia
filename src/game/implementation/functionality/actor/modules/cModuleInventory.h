// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"
#include "../engine/iModule.h"
#include "framework/world_structure/cObject.h"

namespace Forradia {

class cModuleInventory : public iModule {
 public:
  using iModule::iModule;

  void ResetForNewFrame() override;
  void Update() override;

  // Collection operations

  void Add(int Position, std::string ObjectName);

  // Collection structure

  UMap<int, SPtr<cObject>> Objects;
};

}  // namespace Forradia
