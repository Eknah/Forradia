// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cModuleInventory.h"

namespace Forradia {

void cModuleInventory::ResetForNewFrame() {}

void cModuleInventory::Update() {}

void cModuleInventory::Add(int Position, std::string ObjectName) {
  Objects.insert({Position, MakeUPtr<cObject>(ObjectName)});
}

}  // namespace Forradia
