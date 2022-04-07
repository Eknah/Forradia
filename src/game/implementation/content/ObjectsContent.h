// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <tuple>
#include <vector>
#include "../engine/Aliases.h"
#include "ObjectDescription.h"
#include "../engine/eObjectFlags.h"

namespace Forradia {

class cObjectsContent {
 public:
  // Collection operations

  void Add(std::string objectName, cObjectDescription description);
  void Add(std::string objectName, char flags);
  void AddMany(std::vector<std::tuple<std::string, char>>
           descriptions);

  void SetOpacity(std::string objectName, float opacity);

  // Get info about an object

  bool IsMovable(int objectType) const;
  bool BlocksMovement(int objectType) const;

  // Collection structure

  UMap<int, cObjectDescription> objectDescriptions;
};

}  // namespace Forradia
