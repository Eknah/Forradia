// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ObjectsContent.h"
#include "../engine/Aliases.h"
#include "ObjectDescription.h"
#include "../engine/eObjectFlags.h"

namespace Forradia {

void cObjectsContent::Add(std::string objectName,
                          cObjectDescription description) {
  objectDescriptions.insert({GetId(objectName), description});
}

void cObjectsContent::Add(std::string objectName,
                          char flags) {
    objectDescriptions.insert({GetId(objectName),
                               cObjectDescription(flags)});
}

void cObjectsContent::AddMany(std::vector<std::tuple<std::string, char>>
         descriptions) {
    for (auto& desc : descriptions) {
        auto objectName = std::get<0>(desc);
        auto flags = std::get<1>(desc);

        objectDescriptions.insert({GetId(objectName),
                                   cObjectDescription(flags)});
    }
}

void cObjectsContent::SetOpacity(std::string objectName, float opacity) {
    objectDescriptions.at(GetId(objectName)).opacity = opacity;
}

bool cObjectsContent::IsMovable(int objectType) const {
  if (objectDescriptions.count(objectType))
    return objectDescriptions.at(objectType).flags & ObjectMovable;

  return false;
}

bool cObjectsContent::BlocksMovement(int objectType) const {
  if (objectDescriptions.count(objectType))
    return objectDescriptions.at(objectType).flags & ObjectMovementBlock;

  return false;
}

}  // namespace Forradia
