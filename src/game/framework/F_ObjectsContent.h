#pragma once
#include "../core/Aliases.h"
#include "F_ObjectDescription.h"

namespace Forradia
{

class F_ObjectsContent
{

public:

    // Collection operations
    void Add(std::string objectName, F_ObjectDescription description);

    // Get info about an object
    bool IsMovable(int objectType);
    bool BlocksMovement(int objectType);
    bool BlocksSight(int objectType);

    // Collection structure
    UMap<int, F_ObjectDescription> ObjectDescriptions;

};

}
