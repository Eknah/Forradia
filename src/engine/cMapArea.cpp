// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cMapArea.h"
#include "framework/world_structure/cTile.h"

namespace Forradia {

cMapArea::cMapArea(const iEngine &Engine, int Size_, int WorldX, int WorldY, int WorldZ)
    : Size(Size_), WorldCoord({WorldX, WorldY, WorldZ}) {
  for (auto x = 0; x < Size; x++) {
    Tiles.push_back(std::vector<cTile>());

    for (auto y = 0; y < Size; y++)
      Tiles[x].push_back(cTile(Engine));
  }
}

cActor& cMapArea::AddActor(UPtr<cActor> Actor, int TileX, int TileY) {
    Tiles[TileX][TileY].Actor = std::move(Actor);
    return *Tiles[TileX][TileY].Actor;
  }

bool cMapArea::IsUnderground() {
      return WorldCoord.Z < 0;
  }

cTile &cMapArea::GetTile(cPoint2 Pos) {
    return Tiles[Pos.X][Pos.Y];
  }

}  // namespace Forradia
