// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"

namespace Forradia {

class IEngine;
class PlanetWorldMap;

class IMapGenerator {
 public:
  IMapGenerator(const IEngine &_e, const UPtr<PlanetWorldMap> &_worldMap)
      : e(_e), worldMap(_worldMap) {}

  // Core map area generation

  virtual void GenerateMapArea(Point3 worldPos) const = 0;

 protected:
  const IEngine &e;
  const UPtr<PlanetWorldMap> &worldMap;
};

}  // namespace Forradia
