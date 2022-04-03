// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <vector>
#include "../engine/Aliases.h"
#include "implementation/functionality/actor/cActor.h"
#include "../engine/eObjectFlags.h"
#include "framework/world_structure/cObject.h"

namespace Forradia {

class iEngine;

class cTile {
 public:
  explicit cTile(const iEngine &Engine_) : engine(Engine_) {}

  // Get info about tile

  bool HasObjectWithFlag(eObjectFlags Flag);
  bool HasObjectOfType(std::string ObjectName);

  // Core tile data structure

  int groundType = 0;
  std::vector<SPtr<cObject>> objects;
  int elevation = 0;
  SPtr<cActor> actor = nullptr;
  std::unordered_map<std::string, std::string> properties;

 private:
  const iEngine &engine;
};

}  // namespace Forradia
