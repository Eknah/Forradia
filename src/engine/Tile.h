// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <vector>
#include "../engine/Aliases.h"
#include "implementation/functionality/actor/Actor.h"
#include "../engine/eObjectFlags.h"
#include "framework/worldStructure/Object.h"

namespace Forradia {

class iEngine;

class cTile {
 public:
  explicit cTile(const iEngine &_engine) : engine(_engine) {}

  // Get info about tile

  bool HasObjectWithFlag(eObjectFlags flag);
  bool HasObjectOfType(std::string objectName);

  // Core tile data structure

  int groundType = 0;
  std::vector<SPtr<cObject>> objects;
  SPtr<cObject> roof;
  int elevation = 0;
  SPtr<cActor> actor = nullptr;
  std::unordered_map<std::string, std::string> properties;

 private:
  const iEngine &engine;
};

}  // namespace Forradia
