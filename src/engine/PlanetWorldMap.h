// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/MapArea.h"
#include "Rect.h"

namespace Forradia {

class iMapGenerator;

class cPlanetWorldMap {
 public:
  explicit cPlanetWorldMap(int _mapAreaSize,
                     int _worldMapWidth,
                     int _worldMapHeight) :
        mapAreaSize(_mapAreaSize), worldMapWidth(_worldMapWidth),
        worldMapHeight(_worldMapHeight) {}

  // Core

    void GenerateWorldMap(UMap<int, UMap<int, SPtr<iMapGenerator>>> genAreas);
    cRect GetBounds();

  UPtr<cMapArea>& GetArea(cPoint3 pos);

  // Basic data

  int mapAreaSize = -1;
  int worldMapWidth = -1;
  int worldMapHeight = -1;

  // Core world map data structures

  UMap<int, UMap<int, UMap<int, UPtr<cMapArea>>>> areas;
};

}  // namespace Forradia
