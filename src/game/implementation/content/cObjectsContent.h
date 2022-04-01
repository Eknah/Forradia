// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <tuple>
#include <vector>
#include "../engine/Aliases.h"
#include "cObjectDescription.h"
#include "../engine/eObjectFlags.h"

namespace Forradia {

class cObjectsContent {
 public:
  // Collection operations

  void Add(std::string ObjectName, cObjectDescription Description);
  void Add(std::string ObjectName, eObjectFlags Flags);
  void AddMany(std::vector<std::tuple<std::string, eObjectFlags>>
           Descriptions);

  // Get info about an object

  bool IsMovable(int ObjectType) const;
  bool BlocksMovement(int ObjectType) const;

  // Collection structure

  UMap<int, cObjectDescription> ObjectDescriptions;
};

}  // namespace Forradia
