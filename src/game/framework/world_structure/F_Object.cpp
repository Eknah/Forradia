
#include "CommonExternal.h"
#include "F_Object.h"

namespace Forradia
{

F_Object::F_Object(std::string _objectTypeName, bool randomScaling) : ObjectType(GetId(_objectTypeName)), Rotation((float)(rand() % 360))
{
    if (randomScaling)
        Scaling = 0.6f + float(rand() % 8) / 10.0f;
}

void F_Object::UseOn(std::unique_ptr<F_Object>& other)
{
    if (ObjectType == GetId("ObjectWoodaxe") && (other->ObjectType == GetId("ObjectTree1") || other->ObjectType == GetId("ObjectTree2")))
        other->TransformInto("ObjectFelledTree");

    if (ObjectType == GetId("ObjectSaw") && other->ObjectType == GetId("ObjectFelledTree"))
        other->TransformInto("ObjectWoodplank");
}

void F_Object::TransformInto(std::string objectName)
{
    ObjectType = GetId(objectName);
}

}
