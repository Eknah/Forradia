
#include "cObjectsContent.h"
#include "../engine/Aliases.h"
#include "cObjectDescription.h"

namespace Forradia
{

void cObjectsContent::Add(std::string ObjectName, cObjectDescription Description)
{
    ObjectDescriptions.insert({GetId(ObjectName), Description});
}

bool cObjectsContent::IsMovable(int ObjectType)
{
    if (ObjectDescriptions.count(ObjectType))
        return ObjectDescriptions.at(ObjectType).Movable;

    return false;
}

bool cObjectsContent::BlocksMovement(int ObjectType)
{
    if (ObjectDescriptions.count(ObjectType))
        return ObjectDescriptions.at(ObjectType).BlocksMovement;

    return false;
}

bool cObjectsContent::BlocksSight(int ObjectType)
{
    if (ObjectDescriptions.count(ObjectType))
        return ObjectDescriptions.at(ObjectType).BlocksSight;

    return false;
}

}
