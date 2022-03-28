// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cQuestCaveMapGenerator.h"

namespace Forradia {

void cQuestCaveMapGenerator::GenerateQuestCaveMapArea(
    cMapArea *MapArea, cPoint2 EntranceLocation) {
  ClearToCaveFloor(MapArea);
  GenerateCaveWalls(MapArea);
  GeneratePath(MapArea, EntranceLocation);

  MapArea->Tiles[EntranceLocation.X][EntranceLocation.Y].WarpToFloor = 0;
  MapArea->Tiles[EntranceLocation.X][EntranceLocation.Y].Objects.push_back(
      MakeUPtr<cObject>("ObjectQuestCaveEntrance"));
}

void cQuestCaveMapGenerator::ClearToCaveFloor(cMapArea *MapArea) {
  for (auto TileY = 0; TileY < MapArea->Size; TileY++)
    for (auto TileX = 0; TileX < MapArea->Size; TileX++)

      MapArea->Tiles[TileX][TileY].GroundType = GetId("GroundtypeCaveFloor");
}

void cQuestCaveMapGenerator::GenerateCaveWalls(cMapArea *MapArea) {
  for (auto TileY = 0; TileY < MapArea->Size; TileY++)
    for (auto TileX = 0; TileX < MapArea->Size; TileX++)

      MapArea->Tiles[TileX][TileY].Objects.push_back(
          MakeUPtr<cObject>("ObjectCaveWallBlock", false));
}

void cQuestCaveMapGenerator::GeneratePath(cMapArea *MapArea,
                                          cPoint2 EntranceLocation) {
  for (auto TileY = EntranceLocation.Y - 3; TileY <= EntranceLocation.Y + 3;
       TileY++)
    for (auto TileX = EntranceLocation.X - 3; TileX <= EntranceLocation.X + 3;
         TileX++)

      MapArea->Tiles[TileX][TileY].Objects.clear();

  auto TileX = EntranceLocation.X;
  auto TileY = EntranceLocation.Y;

  for (auto I = 0; I < 20; I++) {
    auto Direction = Random.Next() % 4;
    auto NumSteps = 4 + Random.Next() % 20;

    for (auto J = 0; J < NumSteps; J++) {
      for (auto XX = TileX - 1; XX <= TileX + 1; XX++) {
        for (auto YY = TileY - 1; YY <= TileY + 1; YY++) {
          if (XX >= 0 && YY >= 0 && XX < MapArea->Size && YY < MapArea->Size)
            if (MapArea->Tiles[XX][YY].Objects.size() > 0)
              if (!MapArea->Tiles[XX][YY].HasObjectOfType(
                      "ObjectQuestCaveEntrance"))
                MapArea->Tiles[XX][YY].Objects.clear();
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
