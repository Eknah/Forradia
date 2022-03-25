#include "CObjectsContent.h"
#include "../Hidden/Aliases.h"
#include "CObjectDescription.h"
namespace Forradia
{

void CObjectsContent::Add(String objectName, CObjectDescription description)
{
    ObjectDescriptions.insert({GetId(objectName), description});
}
bool CObjectsContent::IsMovable(int objectType)
{
    if (ObjectDescriptions.count(objectType))
        return ObjectDescriptions.at(objectType).Movable;
    return false;
}
bool CObjectsContent::BlocksMovement(int objectType)
{
    if (ObjectDescriptions.count(objectType))
        return ObjectDescriptions.at(objectType).BlocksMovement;
    return false;
}
bool CObjectsContent::BlocksSight(int objectType)
{
    if (ObjectDescriptions.count(objectType))
        return ObjectDescriptions.at(objectType).BlocksSight;
    return false;
}
}
