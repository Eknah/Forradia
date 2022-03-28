// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"
#include "../engine/cPoint2F.h"
#include "../engine/cPoint3.h"
#include "framework/world_structure/cMob.h"
#include "framework/world_structure/cTile.h"

namespace Forradia {

class cEngine;

class cMapArea {
 public:
  cMapArea(const cEngine &Engine, int Size_, int WorldX, int WorldY, int WorldZ)
      : Size(Size_), WorldCoord({WorldX, WorldY, WorldZ}) {
    for (auto x = 0; x < Size; x++) {
      Tiles.push_back(std::vector<cTile>());

      for (auto y = 0; y < Size; y++)
        Tiles[x].push_back(cTile(Engine));
    }
  }

  inline bool IsUnderground() { return WorldCoord.Z < 0; }

  // Basic data
  cPoint3 WorldCoord = {-1, -1, -1};
  cPoint2F PlayerSpawnPosition = {-1, -1};
  int Size = -1;

  // Map structure of tiles and mobs
  std::vector<std::vector<cTile>> Tiles;
  std::vector<std::reference_wrapper<UPtr<cMob>>> MobsMirror;
};

}  // namespace Forradia
