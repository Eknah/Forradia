// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cInventory.h"

namespace Forradia {

void cInventory::Add(std::string ObjectName) {
    for (auto i = 0; i <= Objects.size(); i++) {
        if (Objects.count(i) == 0) {
            Objects.insert({i, MakeSPtr<cObject>(ObjectName)});
            return;
        }
    }
}

void cInventory::Add(std::vector<std::string> ObjectNames) {
    for (auto& name : ObjectNames) {
        Add(name);
    }
}

}  // namespace Forradia
