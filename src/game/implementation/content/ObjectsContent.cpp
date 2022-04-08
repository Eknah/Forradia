// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ObjectsContent.h"
#include "../engine/Aliases.h"
#include "ObjectDescription.h"
#include "../engine/ObjectFlags.h"

namespace Forradia {

void ObjectsContent::Add(std::string objectName,
                          ObjectDescription description) {
  objectDescriptions.insert({GetId(objectName), description});
}

void ObjectsContent::Add(std::string objectName,
                          char flags) {
    objectDescriptions.insert({GetId(objectName),
                               ObjectDescription(flags)});
}

void ObjectsContent::AddMany(std::vector<std::tuple<std::string, char>>
         descriptions) {
    for (auto& desc : descriptions) {
        auto objectName = std::get<0>(desc);
        auto flags = std::get<1>(desc);

        objectDescriptions.insert({GetId(objectName),
                                   ObjectDescription(flags)});
    }
}

void ObjectsContent::SetOpacity(std::string objectName, float opacity) {
    objectDescriptions.at(GetId(objectName)).opacity = opacity;
}

bool ObjectsContent::IsMovable(int objectType) const {
  if (objectDescriptions.count(objectType))
    return objectDescriptions.at(objectType).flags & ObjMovable;

  return false;
}

bool ObjectsContent::BlocksMovement(int objectType) const {
  if (objectDescriptions.count(objectType))
    return objectDescriptions.at(objectType).flags & ObjObstacle;

  return false;
}

}  // namespace Forradia
