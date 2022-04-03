// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Aliases.h"

namespace Forradia {

class cObject;

class cInventory {
public:
    void Add(std::string objectName);
    void AddMany(std::vector<std::string> objectNames);

    UMap<int, SPtr<cObject>> objects;
};

}  // namespace Forradia
