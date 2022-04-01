// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cObject.h"

namespace Forradia {

cObject::cObject(std::string ObjectTypeName, bool RandomScaling)
    : ObjectType(GetId(ObjectTypeName)) {
  Rotation = static_cast<float>(Random.Next() % 360);
    if (RandomScaling)
    Scaling = 0.6f + static_cast<float>(Random.Next() % 8) / 10.0f;
}

void cObject::UseOn(const std::shared_ptr<cObject> &Other) {
  if (ObjectType == GetId("ObjectWoodaxe") &&
      (Other->ObjectType == GetId("ObjectTree1") ||
       Other->ObjectType == GetId("ObjectTree2")))
    Other->TransformInto("ObjectFelledTree");

  if (ObjectType == GetId("ObjectSaw") &&
      Other->ObjectType == GetId("ObjectFelledTree"))
    Other->TransformInto("ObjectWoodplank");
}

void cObject::TransformInto(std::string ObjectName) {
  ObjectType = GetId(ObjectName);
}

}  // namespace Forradia
