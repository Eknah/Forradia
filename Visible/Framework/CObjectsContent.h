#pragma once
namespace Forradia
{

class CObjectsContent
{

public:

    // Collection operations
    void Add(String objectName, CObjectDescription description);

    // Get info about an object
    bool IsMovable(int objectType);
    bool BlocksMovement(int objectType);
    bool BlocksSight(int objectType);

    // Collection structure
    UMap<int, CObjectDescription> ObjectDescriptions;

};

}
