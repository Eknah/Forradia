// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Object.h"

namespace Forradia {

cObject::cObject(std::string ObjectTypeName, bool RandomScaling,
                 bool RandomRotation, float _rotation)
    : objectType(GetId(ObjectTypeName)) {
    if (RandomRotation)
  rotation = static_cast<float>(random.Next() % 360);
    else rotation = _rotation;

    if (RandomScaling)
    scaling = 0.6f + static_cast<float>(random.Next() % 8) / 10.0f;
}

void cObject::UseOn(const std::shared_ptr<cObject> &Other) {
  if (objectType == GetId("ObjectWoodaxe") &&
      (Other->objectType == GetId("ObjectTree1") ||
       Other->objectType == GetId("ObjectTree2")))
    Other->TransformInto("ObjectFelledTree");

  if (objectType == GetId("ObjectSaw") &&
      Other->objectType == GetId("ObjectFelledTree"))
    Other->TransformInto("ObjectWoodplank");
}

void cObject::TransformInto(std::string ObjectName) {
  objectType = GetId(ObjectName);
}

}  // namespace Forradia
