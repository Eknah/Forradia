// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <vector>
#include "../engine/Aliases.h"
#include "implementation/functionality/actor/cActor.h"
#include "cObject.h"

namespace Forradia {

class iEngine;

class cTile {
 public:
  explicit cTile(const iEngine &Engine_) : Engine(Engine_) {}

  // Get info about tile

  bool MovementBlocked();
  bool HasObjectOfType(std::string ObjectName);

  // Core tile data structure

  int GroundType = 0;
  std::vector<UPtr<cObject>> Objects;
  int Elevation = 0;
  UPtr<cActor> Actor = nullptr;
  int WarpToFloor = -1;

 private:
  const iEngine &Engine;
};

}  // namespace Forradia
