#pragma once
#include "../core/Aliases.h"
#include "world_structure/F_Object.h"

namespace Forradia
{

class F_Inventory
{

public:

    // Collection operations
    void Add(int position, std::string objectName);

    // Collection structure
    UMap<int, SPtr<F_Object>> Objects;

};

}
