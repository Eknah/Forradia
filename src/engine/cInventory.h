// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../game/framework/world_structure/cObject.h"

namespace Forradia {

class cInventory {
public:
    UMap<int, SPtr<cObject>> Objects;
};

}  // namespace Forradia
