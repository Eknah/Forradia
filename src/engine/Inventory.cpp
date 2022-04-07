// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Inventory.h"
#include "../game/framework/worldStructure/Object.h"

namespace Forradia {

void cInventory::Add(std::string objectName) {
    for (auto i = 0; i <= objects.size(); i++) {
        if (objects.count(i) == 0) {
            objects.insert({i, MakeSPtr<cObject>(objectName)});
            return;
        }
    }
}

void cInventory::AddMany(std::vector<std::string> objectNames) {
    for (auto& name : objectNames) {
        Add(name);
    }
}

}  // namespace Forradia
