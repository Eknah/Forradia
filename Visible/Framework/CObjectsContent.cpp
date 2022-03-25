#include "Common.h"
#include "CObjectsContent.h"
namespace Forradia
{

    void CObjectsContent::Add(String objectName, CObjectDescription description)
    {
        ObjectDescriptions.insert({Hash(objectName), description});
    }
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
