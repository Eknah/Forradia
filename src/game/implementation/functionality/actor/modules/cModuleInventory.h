// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "../engine/Aliases.h"
#include "../engine/iModule.h"
#include "../engine/cInventory.h"

namespace Forradia {

class cModuleInventory : public iModule {
 public:
  using iModule::iModule;

  void ResetForNewFrame() override;
  void Update() override;

  // Collection operations

  void Add(int position, std::string objectName);

  // Collection structure

  //UMap<int, SPtr<cObject>> Objects;
  cInventory inventory;
};

}  // namespace Forradia
