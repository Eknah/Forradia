
#include "CommonExternal.h"
#include "cTile.h"
#include "../engine/cEngine.h"

namespace Forradia
{

bool cTile::MovementBlocked()
{
    if (GroundType == GetId("GroundtypeWater")) return true;

    for (auto& Object : Objects)
        if (Engine.ObjectsContent.BlocksMovement(Object->ObjectType)) return true;

    return false;
}

bool cTile::HasObjectOfType(std::string objectName)
{
    for (auto& Object : Objects)
        if (Object->ObjectType == GetId(objectName)) return true;

    return false;
}

}
