// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <vector>
#include <utility>
#include "../engine/Aliases.h"
#include "../engine/Point2F.h"
#include "../engine/Point3.h"
#include "../engine/Point2.h"
#include "framework/worldStructure/Mob.h"
#include "../engine/Tile.h"

namespace Forradia {

class iEngine;

class cMapArea {
 public:
  cMapArea(const iEngine &engine, int _size, int worldx, int worldy, int worldz);

  cActor& AddActor(UPtr<cActor> actor, int tilex, int tiley);

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
