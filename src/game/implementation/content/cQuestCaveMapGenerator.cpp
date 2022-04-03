// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cQuestCaveMapGenerator.h"
#include "framework/world_structure/cObject.h"

namespace Forradia {

void cQuestCaveMapGenerator::GenerateQuestCaveMapArea(
    cMapArea *MapArea, cPoint2 EntranceLocation) {
  ClearToCaveFloor(MapArea);
  GenerateCaveWalls(MapArea);
  GeneratePath(MapArea, EntranceLocation);

  MapArea->tiles[EntranceLocation.x][EntranceLocation.y].properties["WarpToFloor"] = "0";
  MapArea->tiles[EntranceLocation.x][EntranceLocation.y].objects.push_back(
      MakeSPtr<cObject>("ObjectQuestCaveEntrance"));
}

void cQuestCaveMapGenerator::ClearToCaveFloor(cMapArea *MapArea) {
  for (auto TileY = 0; TileY < MapArea->size; TileY++)
    for (auto TileX = 0; TileX < MapArea->size; TileX++)

      MapArea->tiles[TileX][TileY].groundType = GetId("GroundtypeCaveFloor");
}

void cQuestCaveMapGenerator::GenerateCaveWalls(cMapArea *MapArea) {
  for (auto TileY = 0; TileY < MapArea->size; TileY++)
    for (auto TileX = 0; TileX < MapArea->size; TileX++)

      MapArea->tiles[TileX][TileY].objects.push_back(
          MakeSPtr<cObject>("ObjectCaveWallBlock", false));
}

void cQuestCaveMapGenerator::GeneratePath(cMapArea *MapArea,
                                          cPoint2 EntranceLocation) {
  for (auto TileY = EntranceLocation.y - 3; TileY <= EntranceLocation.y + 3;
       TileY++)
    for (auto TileX = EntranceLocation.x - 3; TileX <= EntranceLocation.x + 3;
         TileX++)

      MapArea->tiles[TileX][TileY].objects.clear();

  auto TileX = EntranceLocation.x;
  auto TileY = EntranceLocation.y;

  for (auto I = 0; I < 20; I++) {
    auto Direction = Random.Next() % 4;
    auto NumSteps = 4 + Random.Next() % 20;

    for (auto J = 0; J < NumSteps; J++) {
      for (auto XX = TileX - 1; XX <= TileX + 1; XX++) {
        for (auto YY = TileY - 1; YY <= TileY + 1; YY++) {
          if (XX >= 0 && YY >= 0 && XX < MapArea->size && YY < MapArea->size)
            if (MapArea->tiles[XX][YY].objects.size() > 0)
              if (!MapArea->tiles[XX][YY].HasObjectOfType(
                      "ObjectQuestCaveEntrance"))
                MapArea->tiles[XX][YY].objects.clear();
        }
      }

      switch (Direction) {
      case 0: {
        TileX++;

        break;
      }
      case 1: {
        TileY++;

        break;
      }
      case 2: {
        TileX--;

        break;
      }
      case 3: {
        TileY--;

        break;
      }
      }
    }
  }
}

}  // namespace Forradia
