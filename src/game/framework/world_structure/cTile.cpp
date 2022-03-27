
#include "CommonExternal.h"
#include "cTile.h"
#include "../engine/cEngine.h"

namespace Forradia
{

bool cTile::MovementBlocked()
{
    if (GroundType == GetId("GroundtypeWater")) return true;

    for (auto& object : Objects)
        if (Engine.ObjectsContent.BlocksMovement(object->ObjectType)) return true;

    return false;
}

bool cTile::HasObjectOfType(std::string objectName)
{
    for (auto& object : Objects)
        if (object->ObjectType == GetId(objectName)) return true;

    return false;
}

}
