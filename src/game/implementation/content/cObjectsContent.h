// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "../engine/Aliases.h"
#include "cObjectDescription.h"

namespace Forradia {

class cObjectsContent {
 public:
  // Collection operations

  void Add(std::string ObjectName, cObjectDescription Description);

  // Get info about an object

  bool IsMovable(int ObjectType) const;
  bool BlocksMovement(int ObjectType) const;
  bool BlocksSight(int ObjectType) const;

  // Collection structure

  UMap<int, cObjectDescription> ObjectDescriptions;
};

}  // namespace Forradia
