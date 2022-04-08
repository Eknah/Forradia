// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Object.h"

namespace Forradia {

cObject::cObject(std::string objectTypeName, bool randomScaling,
                 bool randomRotation, float _rotation)
    : objectType(GetId(objectTypeName)) {
    if (randomRotation)
  rotation = static_cast<float>(random.Next() % 360);
    else rotation = _rotation;

    if (randomScaling)
    scaling = 0.6f + static_cast<float>(random.Next() % 8) / 10.0f;
}

void cObject::UseOn(const std::shared_ptr<cObject> &other) {
  if (objectType == GetId("ObjectWoodaxe") &&
      (other->objectType == GetId("ObjectTree1") ||
       other->objectType == GetId("ObjectTree2")))
    other->TransformInto("ObjectFelledTree");

  if (objectType == GetId("ObjectSaw") &&
      other->objectType == GetId("ObjectFelledTree"))
    other->TransformInto("ObjectWoodplank");
}

void cObject::TransformInto(std::string objectName) {
  objectType = GetId(objectName);
}

}  // namespace Forradia
