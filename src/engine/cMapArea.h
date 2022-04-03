// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <vector>
#include <utility>
#include "../engine/Aliases.h"
#include "../engine/cPoint2F.h"
#include "../engine/cPoint3.h"
#include "../engine/cPoint2.h"
#include "framework/world_structure/cMob.h"
#include "../engine/cTile.h"

namespace Forradia {

class iEngine;

class cMapArea {
 public:
  cMapArea(const iEngine &Engine, int Size_, int WorldX, int WorldY, int WorldZ);

  cActor& AddActor(UPtr<cActor> Actor, int TileX, int TileY);

  bool IsUnderground();

  cTile &GetTile(cPoint2 Pos);

  // Basic data
  cPoint3 worldCoord = {-1, -1, -1};
  cPoint2F spawnPos = {-1, -1};
  int size = -1;

  // Map structure of tiles and mobs
  std::vector<std::vector<cTile>> tiles;
  std::vector<std::reference_wrapper<SPtr<cActor>>> mobActorsMirror;
};

}  // namespace Forradia
