#pragma once
#include "../Hidden/Aliases.h"
#include "WorldStructure/CObject.h"
namespace Forradia
{

class CInventory
{

public:

    // Collection operations
    void Add(int position, String objectName);

    // Collection structure
    UMap<int, SPtr<CObject>> Objects;

};

}
