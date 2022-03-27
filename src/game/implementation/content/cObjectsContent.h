
#pragma once
#include "../engine/Aliases.h"
#include "cObjectDescription.h"

namespace Forradia
{

class cObjectsContent
{

public:

    // Collection operations
    void Add(std::string objectName, cObjectDescription description);

    // Get info about an object
    bool IsMovable(int objectType);
    bool BlocksMovement(int objectType);
    bool BlocksSight(int objectType);

    // Collection structure
    UMap<int, cObjectDescription> ObjectDescriptions;

};

}
