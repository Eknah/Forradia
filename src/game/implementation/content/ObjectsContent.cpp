// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ObjectsContent.h"
#include "../engine/Aliases.h"
#include "ObjectDescription.h"
#include "../engine/eObjectFlags.h"

namespace Forradia {

void cObjectsContent::Add(std::string ObjectName,
                          cObjectDescription Description) {
  objectDescriptions.insert({GetId(ObjectName), Description});
}

void cObjectsContent::Add(std::string ObjectName,
                          char Flags) {
    objectDescriptions.insert({GetId(ObjectName),
                               cObjectDescription(Flags)});
}

void cObjectsContent::AddMany(std::vector<std::tuple<std::string, char>>
         Descriptions) {
    for (auto& desc : Descriptions) {
        auto objectName = std::get<0>(desc);
        auto flags = std::get<1>(desc);

        objectDescriptions.insert({GetId(objectName),
                                   cObjectDescription(flags)});
    }
}

void cObjectsContent::SetOpacity(std::string ObjectName, float opacity) {
    objectDescriptions.at(GetId(ObjectName)).opacity = opacity;
}

bool cObjectsContent::IsMovable(int ObjectType) const {
  if (objectDescriptions.count(ObjectType))
    return objectDescriptions.at(ObjectType).flags & ObjectMovable;

  return false;
}

bool cObjectsContent::BlocksMovement(int ObjectType) const {
  if (objectDescriptions.count(ObjectType))
    return objectDescriptions.at(ObjectType).flags & ObjectMovementBlock;

  return false;
}

}  // namespace Forradia
