#include "F_ObjectsContent.h"
#include "../core/Aliases.h"
#include "F_ObjectDescription.h"

namespace Forradia
{

void F_ObjectsContent::Add(std::string objectName, F_ObjectDescription description)
{
    ObjectDescriptions.insert({GetId(objectName), description});
}

bool F_ObjectsContent::IsMovable(int objectType)
{
    if (ObjectDescriptions.count(objectType))
        return ObjectDescriptions.at(objectType).Movable;

    return false;
}

bool F_ObjectsContent::BlocksMovement(int objectType)
{
    if (ObjectDescriptions.count(objectType))
        return ObjectDescriptions.at(objectType).BlocksMovement;

    return false;
}

bool F_ObjectsContent::BlocksSight(int objectType)
{
    if (ObjectDescriptions.count(objectType))
        return ObjectDescriptions.at(objectType).BlocksSight;

    return false;
}

}
