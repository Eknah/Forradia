// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ModuleInventory.h"
#include "framework/worldStructure/Object.h"

namespace Forradia {

void ModuleInventory::ResetForNewFrame() {}

void ModuleInventory::Update() {}

void ModuleInventory::Add(int position, std::string objectName) {
  inventory.objects.insert({position, MakeSPtr<Object>(objectName)});
}

}  // namespace Forradia
