
#include "CommonExternal.h"
#include "cObject.h"

namespace Forradia
{

cObject::cObject(std::string _objectTypeName, bool randomScaling) : ObjectType(GetId(_objectTypeName)), Rotation((float)(rand() % 360))
{
    if (randomScaling)
        Scaling = 0.6f + float(rand() % 8) / 10.0f;
}

void cObject::UseOn(std::unique_ptr<cObject>& other)
{
    if (ObjectType == GetId("ObjectWoodaxe") && (other->ObjectType == GetId("ObjectTree1") || other->ObjectType == GetId("ObjectTree2")))
        other->TransformInto("ObjectFelledTree");

    if (ObjectType == GetId("ObjectSaw") && other->ObjectType == GetId("ObjectFelledTree"))
        other->TransformInto("ObjectWoodplank");
}

void cObject::TransformInto(std::string objectName)
{
    ObjectType = GetId(objectName);
}

}
