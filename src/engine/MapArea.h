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

class IEngine;

class MapArea {
 public:
  MapArea(const IEngine &e, int _size, int worldx, int worldy, int worldz);

  Actor& AddActor(UPtr<Actor> actor, int tilex, int tiley);

  bool IsUnderground();

  Tile &GetTile(Point2 Pos);

  // Basic data
  Point3 worldCoord = {-1, -1, -1};
  Point2F spawnPos = {-1, -1};
  int size = -1;

  // Map structure of tiles and mobs
  std::vector<std::vector<Tile>> tiles;
  std::vector<std::reference_wrapper<SPtr<Actor>>> mobActorsMirror;
};

}  // namespace Forradia
