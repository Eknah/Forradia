// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"

namespace Forradia {

class IEngine;
class PlanetWorldMap;

class IMapGenerator {
 public:
  IMapGenerator(const IEngine &Engine_, const UPtr<PlanetWorldMap> &_worldMap)
      : engine(Engine_), worldMap(_worldMap) {}

  // Core map area generation

  virtual void GenerateMapArea(int WorldX, int WorldY, int WorldZ) const = 0;

 protected:
  const IEngine &engine;
  const UPtr<PlanetWorldMap> &worldMap;
};

}  // namespace Forradia
