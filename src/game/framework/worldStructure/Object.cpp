// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Object.h"

namespace Forradia
{

    Object::Object(String objectTypeName, bool randomScaling, bool randomRotation, float _rotation) : objectType(GetId(objectTypeName))
    {
        if (randomRotation)
            rotation = CFloat(random.Next() % 360);
        else rotation = _rotation;

        if (randomScaling)
            scaling = 0.6f + CFloat(random.Next() % 8) / 10.0f;
    }

    void Object::UseOn(const SPtr<Object>& other)
    {
        if (objectType == GetId("ObjectWoodaxe") &&
            (other->objectType == GetId("ObjectTree1") || other->objectType == GetId("ObjectTree2")))
                other->TransformInto("ObjectFelledTree");

        if (objectType == GetId("ObjectSaw") && other->objectType == GetId("ObjectFelledTree"))
            other->TransformInto("ObjectWoodplank");
    }

    void Object::TransformInto(String objectName)
    {
        objectType = GetId(objectName);
    }

}  // namespace Forradia
