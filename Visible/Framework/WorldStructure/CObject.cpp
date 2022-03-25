#include "Common.h"
#include "CObject.h"
namespace Forradia
{
    CObject::CObject(std::string _objectTypeName, bool randomScaling) : ObjectType(Hash(_objectTypeName)), Rotation(rand() % 360)
	{
		if (randomScaling)
			Scaling = 0.6f + float(rand() % 8) / 10.0f;
	}
    void CObject::UseOn(std::unique_ptr<CObject>& other)
	{
		if (ObjectType == Hash("ObjectWoodaxe") && (other->ObjectType == Hash("ObjectTree1") || other->ObjectType == Hash("ObjectTree2")))
			other->TransformInto("ObjectFelledTree");
	}
    void CObject::TransformInto(String objectName)
	{
		ObjectType = Hash(objectName);
	}
}
