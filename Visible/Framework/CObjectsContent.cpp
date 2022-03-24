#include "Pch.h"
#include "CObjectsContent.h"
namespace Forradia
{
	bool CObjectsContent::IsMovable(int objectType)
	{
		if (ObjectDescriptions.count(objectType))
			return ObjectDescriptions.at(objectType).Movable;
		return False;
	}
	bool CObjectsContent::BlocksMovement(int objectType)
	{
		if (ObjectDescriptions.count(objectType))
			return ObjectDescriptions.at(objectType).BlocksMovement;
		return False;
	}
	bool CObjectsContent::BlocksSight(int objectType)
	{
		if (ObjectDescriptions.count(objectType))
			return ObjectDescriptions.at(objectType).BlocksSight;
		return False;
	}
}