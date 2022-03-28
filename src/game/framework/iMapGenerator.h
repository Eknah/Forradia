// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"

namespace Forradia {

class cEngine;
class cWorldMap;

class iMapGenerator {
 public:
  iMapGenerator(cEngine &Engine_, UPtr<cWorldMap> &WorldMap_)
      : Engine(Engine_), WorldMap(WorldMap_) {}

  // Core map area generation

  virtual void GenerateMapArea(int WorldX, int WorldY, int WorldZ) = 0;

 protected:
  cEngine &Engine;
  UPtr<cWorldMap> &WorldMap;
};

}  // namespace Forradia
