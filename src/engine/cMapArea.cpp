// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cMapArea.h"
#include "../engine/cTile.h"

namespace Forradia {

cMapArea::cMapArea(const iEngine &Engine, int Size_, int WorldX, int WorldY, int WorldZ)
    : size(Size_), worldCoord({WorldX, WorldY, WorldZ}) {
  for (auto x = 0; x < size; x++) {
    tiles.push_back(std::vector<cTile>());

    for (auto y = 0; y < size; y++)
      tiles[x].push_back(cTile(Engine));
  }
}

cActor& cMapArea::AddActor(UPtr<cActor> Actor, int TileX, int TileY) {
    tiles[TileX][TileY].actor = std::move(Actor);
    return *tiles[TileX][TileY].actor;
  }

bool cMapArea::IsUnderground() {
      return worldCoord.z < 0;
  }

cTile &cMapArea::GetTile(cPoint2 Pos) {
    return tiles[Pos.x][Pos.y];
  }

}  // namespace Forradia
