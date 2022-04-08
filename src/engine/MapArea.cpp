// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "MapArea.h"
#include "../engine/Tile.h"

namespace Forradia {

MapArea::MapArea(const IEngine &e, int _size, int worldx, int worldy, int worldz)
    : size(_size), worldCoord({worldx, worldy, worldz}) {
  for (auto x = 0; x < size; x++) {
    tiles.push_back(std::vector<Tile>());

    for (auto y = 0; y < size; y++)
      tiles[x].push_back(Tile(e));
  }
}

Actor& MapArea::AddActor(UPtr<Actor> Actor, int TileX, int TileY) {
    tiles[TileX][TileY].actor = std::move(Actor);
    return *tiles[TileX][TileY].actor;
  }

bool MapArea::IsUnderground() {
      return worldCoord.z < 0;
  }

Tile &MapArea::GetTile(Point2 Pos) {
    return tiles[Pos.x][Pos.y];
  }

}  // namespace Forradia
