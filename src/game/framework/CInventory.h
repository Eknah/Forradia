#pragma once
#include "../core/Aliases.h"
#include "world_structure/CObject.h"

namespace Forradia
{

class CInventory
{

public:

    // Collection operations
    void Add(int position, std::string objectName);

    // Collection structure
    UMap<int, SPtr<CObject>> Objects;

};

}
