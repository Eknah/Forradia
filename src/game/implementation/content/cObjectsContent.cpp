
#include "cObjectsContent.h"
#include "../engine/Aliases.h"
#include "cObjectDescription.h"

namespace Forradia
{

void cObjectsContent::Add(std::string objectName, cObjectDescription description)
{
    ObjectDescriptions.insert({GetId(objectName), description});
}

bool cObjectsContent::IsMovable(int objectType)
{
    if (ObjectDescriptions.count(objectType))
        return ObjectDescriptions.at(objectType).Movable;

    return false;
}

bool cObjectsContent::BlocksMovement(int objectType)
{
    if (ObjectDescriptions.count(objectType))
        return ObjectDescriptions.at(objectType).BlocksMovement;

    return false;
}

bool cObjectsContent::BlocksSight(int objectType)
{
    if (ObjectDescriptions.count(objectType))
        return ObjectDescriptions.at(objectType).BlocksSight;

    return false;
}

}
