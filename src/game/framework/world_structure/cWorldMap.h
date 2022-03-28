// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cMapArea.h"

namespace Forradia {

class iMapGenerator;

class cWorldMap {
 public:
  explicit cWorldMap(int MapAreaSize_) : MapAreaSize(MapAreaSize_) {}

  // Core

  void GenerateWorldMap(iMapGenerator &MapGenerator);

  // Basic data

  int MapAreaSize = -1;

  // Core world map data structures

  UMap<int, UMap<int, UMap<int, UPtr<cMapArea>>>> MapAreas;
};

}  // namespace Forradia
