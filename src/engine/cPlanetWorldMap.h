// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cMapArea.h"
#include "cRect.h"

namespace Forradia {

class iMapGenerator;

class cPlanetWorldMap {
 public:
  explicit cPlanetWorldMap(int MapAreaSize_,
                     int WorldMapWidth_,
                     int WorldMapHeight_) :
        mapAreaSize(MapAreaSize_), worldMapWidth(WorldMapWidth_),
        worldMapHeight(WorldMapHeight_) {}

  // Core

    void GenerateWorldMap(UMap<int, UMap<int, SPtr<iMapGenerator>>> GenAreas);
    cRect GetBounds();

  UPtr<cMapArea>& GetArea(cPoint3 Pos);

  // Basic data

  int mapAreaSize = -1;
  int worldMapWidth = -1;
  int worldMapHeight = -1;

  // Core world map data structures

  UMap<int, UMap<int, UMap<int, UPtr<cMapArea>>>> areas;
};

}  // namespace Forradia
