#include "CommonExternal.h"
#include "CObject.h"
namespace Forradia
{
CObject::CObject(std::string _objectTypeName, bool randomScaling) : ObjectType(GetId(_objectTypeName)), Rotation(rand() % 360)
{
    if (randomScaling)
        Scaling = 0.6f + float(rand() % 8) / 10.0f;
}
void CObject::UseOn(std::unique_ptr<CObject>& other)
{
    if (ObjectType == GetId("ObjectWoodaxe") && (other->ObjectType == GetId("ObjectTree1") || other->ObjectType == GetId("ObjectTree2")))
        other->TransformInto("ObjectFelledTree");
}
void CObject::TransformInto(String objectName)
{
    ObjectType = GetId(objectName);
}
}
