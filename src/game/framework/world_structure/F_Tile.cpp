#include "CommonExternal.h"
#include "F_Tile.h"
#include "../core/F_Engine.h"

namespace Forradia
{

bool F_Tile::MovementBlocked()
{
    if (GroundType == GetId("GroundtypeWater")) return true;

    for (auto& object : Objects)
        if (Engine.ObjectsContent.BlocksMovement(object->ObjectType)) return true;

    return false;
}

bool F_Tile::HasObjectOfType(std::string objectName)
{
    for (auto& object : Objects)
        if (object->ObjectType == GetId(objectName)) return true;

    return false;
}

}
