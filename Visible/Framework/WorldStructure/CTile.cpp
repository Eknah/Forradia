#include "Common.h"
#include "CTile.h"
#include "../Hidden/CEngine.h"
namespace Forradia
{
	bool CTile::MovementBlocked()
	{
		if (GroundType == GetId("GroundtypeWater"))
			return True;
		for (auto& object : Objects)
			if (Engine.ObjectsContent.BlocksMovement(object->ObjectType))
				return True;
		return False;
	}

	bool CTile::HasObjectOfType(String objectName)
	{
		for (auto& object : Objects)
			if (object->ObjectType == GetId(objectName))
				return True;
		return False;
	}
}
