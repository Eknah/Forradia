// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cMapArea.h"

namespace Forradia {

class iMapGenerator;

class cWorldMap {
 public:
  explicit cWorldMap(int MapAreaSize_,
                     int WorldMapWidth_,
                     int WorldMapHeight_) :
        MapAreaSize(MapAreaSize_), WorldMapWidth(WorldMapWidth_),
        WorldMapHeight(WorldMapHeight_) {}

  // Core

  void GenerateWorldMap(const iMapGenerator &MapGenerator);

  UPtr<cMapArea>& GetArea(cPoint3 Pos);

  // Basic data

  int MapAreaSize = -1;
  int WorldMapWidth = -1;
  int WorldMapHeight = -1;

  // Core world map data structures

  UMap<int, UMap<int, UMap<int, UPtr<cMapArea>>>> Areas;
};

}  // namespace Forradia
