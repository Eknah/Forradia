// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <vector>
#include "../game/framework/world_structure/cObject.h"

namespace Forradia {

class cInventory {
public:
    void Add(std::string ObjectName);
    void Add(std::vector<std::string> ObjectNames);

    UMap<int, SPtr<cObject>> Objects;
};

}  // namespace Forradia
