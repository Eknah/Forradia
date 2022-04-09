// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "../engine/Aliases.h"
#include "../engine/IModule.h"
#include "../engine/Inventory.h"

namespace Forradia {

class InventoryModule : public IModule {
 public:
  using IModule::IModule;

  void ResetForNewFrame() override;
  void Update() override;

  // Collection operations

  void Add(int position, std::string objectName);

  // Collection structure

  //UMap<int, SPtr<cObject>> Objects;
  Inventory inventory;
};

}  // namespace Forradia
