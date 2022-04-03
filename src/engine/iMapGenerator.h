// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"

namespace Forradia {

class iEngine;
class cPlanetWorldMap;

class iMapGenerator {
 public:
  iMapGenerator(const iEngine &Engine_, const UPtr<cPlanetWorldMap> &WorldMap_)
      : Engine(Engine_), WorldMap(WorldMap_) {}

  // Core map area generation

  virtual void GenerateMapArea(int WorldX, int WorldY, int WorldZ) const = 0;

 protected:
  const iEngine &Engine;
  const UPtr<cPlanetWorldMap> &WorldMap;
};

}  // namespace Forradia
