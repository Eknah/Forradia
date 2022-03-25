#include "Common.h"
#include "CTile.h"
#include "../Hidden/CEngine.h"
namespace Forradia
{
bool CTile::MovementBlocked()
{
    if (GroundType == GetId("GroundtypeWater"))
        return true;
    for (auto& object : Objects)
        if (Engine.ObjectsContent.BlocksMovement(object->ObjectType))
            return true;
    return false;
}

bool CTile::HasObjectOfType(String objectName)
{
    for (auto& object : Objects)
        if (object->ObjectType == GetId(objectName))
            return true;
    return false;
}
}
