// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <vector>
#include "../engine/Aliases.h"
#include "implementation/functionality/actor/cActor.h"
#include "../engine/eObjectFlags.h"
#include "cObject.h"

namespace Forradia {

class iEngine;

class cTile {
 public:
  explicit cTile(const iEngine &Engine_) : Engine(Engine_) {}

  // Get info about tile

  bool HasObjectWithFlag(eObjectFlags Flag);
  bool HasObjectOfType(std::string ObjectName);

  // Core tile data structure

  int GroundType = 0;
  std::vector<SPtr<cObject>> Objects;
  int Elevation = 0;
  SPtr<cActor> Actor = nullptr;
  std::unordered_map<std::string, std::string> Properties;
  //int WarpToFloor = -1;

 private:
  const iEngine &Engine;
};

}  // namespace Forradia
