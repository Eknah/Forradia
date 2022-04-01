// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cObjectsContent.h"
#include "../engine/Aliases.h"
#include "cObjectDescription.h"
#include "eObjectFlags.h"

namespace Forradia {

void cObjectsContent::Add(std::string ObjectName,
                          cObjectDescription Description) {
  ObjectDescriptions.insert({GetId(ObjectName), Description});
}

void cObjectsContent::Add(std::string ObjectName,
                          eObjectFlags Flags) {
    ObjectDescriptions.insert({GetId(ObjectName),
                               cObjectDescription(Flags)});
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
