
#pragma once
#include "../engine/Aliases.h"
#include "cObjectDescription.h"

namespace Forradia
{

class cObjectsContent
{

public:

    // Collection operations

    void    Add(std::string ObjectName, cObjectDescription Description);

    // Get info about an object

    bool    IsMovable(int ObjectType);
    bool    BlocksMovement(int ObjectType);
    bool    BlocksSight(int ObjectType);

    // Collection structure

    UMap<int, cObjectDescription>
    ObjectDescriptions;

};

}
