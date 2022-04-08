// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ModuleInventory.h"
#include "framework/worldStructure/Object.h"

namespace Forradia {

void cModuleInventory::ResetForNewFrame() {}

void cModuleInventory::Update() {}

void cModuleInventory::Add(int position, std::string objectName) {
  inventory.objects.insert({position, MakeSPtr<cObject>(objectName)});
}

}  // namespace Forradia
