// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cObjectsContent.h"
#include "../engine/Aliases.h"
#include "cObjectDescription.h"
#include "../engine/eObjectFlags.h"

namespace Forradia {

void cObjectsContent::Add(std::string ObjectName,
                          cObjectDescription Description) {
  ObjectDescriptions.insert({GetId(ObjectName), Description});
}

void cObjectsContent::Add(std::string ObjectName,
                          char Flags) {
    ObjectDescriptions.insert({GetId(ObjectName),
                               cObjectDescription(Flags)});
}

void cObjectsContent::AddMany(std::vector<std::tuple<std::string, char>>
         Descriptions) {
    for (auto& desc : Descriptions) {
        auto objectName = std::get<0>(desc);
        auto flags = std::get<1>(desc);

        ObjectDescriptions.insert({GetId(objectName),
                                   cObjectDescription(flags)});
    }
}

void cObjectsContent::SetOpacity(std::string ObjectName, float opacity) {
    ObjectDescriptions.at(GetId(ObjectName)).Opacity = opacity;
}

bool cObjectsContent::IsMovable(int ObjectType) const {
  if (ObjectDescriptions.count(ObjectType))
    return ObjectDescriptions.at(ObjectType).Flags & ObjectMovable;

  return false;
}

bool cObjectsContent::BlocksMovement(int ObjectType) const {
  if (ObjectDescriptions.count(ObjectType))
    return ObjectDescriptions.at(ObjectType).Flags & ObjectMovementBlock;

  return false;
}

}  // namespace Forradia
