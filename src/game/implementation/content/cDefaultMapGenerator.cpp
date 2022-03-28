// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cDefaultMapGenerator.h"
#include "cQuestCaveMapGenerator.h"
#include "framework/world_structure/cWorldMap.h"

namespace Forradia {

void cDefaultMapGenerator::GenerateMapArea(int WorldX, int WorldY, int WorldZ) const {
  WorldMap->MapAreas[WorldX][WorldY][WorldZ] =
      MakeUPtr<cMapArea>(Engine, WorldMap->MapAreaSize, WorldX, WorldY, WorldZ);

  auto MapArea = WorldMap->MapAreas[WorldX][WorldY][WorldZ].get();

  ClearToGrass(MapArea);
  GeneratePlayerStartingPosition(MapArea);
  GenerateElevation(MapArea);
  GenerateWater(MapArea);
  GenerateSand(MapArea);
  GenerateClay(MapArea);
  GenerateRock(MapArea);
  GenerateTrees(MapArea);
  GenerateBushes(MapArea);
  GenerateSmallStones(MapArea);
  GeneratePinkFlowers(MapArea);
  GenerateMobs(MapArea);
  GenerateQuestCaves(Engine, MapArea, WorldMap);
}

void cDefaultMapGenerator::ClearToGrass(cMapArea *MapArea) const {
  for (auto TileY = 0; TileY < MapArea->Size; TileY++)
    for (auto TileX = 0; TileX < MapArea->Size; TileX++)

      MapArea->Tiles[TileX][TileY].GroundType = (int)GetId("GroundtypeGrass");
}

void cDefaultMapGenerator::GeneratePlayerStartingPosition(cMapArea *MapArea) const {
  MapArea->PlayerSpawnPosition.X = (float)(rand() % MapArea->Size);
  MapArea->PlayerSpawnPosition.Y = (float)(rand() % MapArea->Size);
}

void cDefaultMapGenerator::GenerateElevation(cMapArea *MapArea) const {
  for (auto I = 0; I < 40; I++) {
    auto CenterTileX = rand() % MapArea->Size;
    auto CenterTileY = rand() % MapArea->Size;
    auto MaxR = 4 + rand() % 12;

    for (auto R = MaxR; R >= 0; R--) {
      for (auto TileY = CenterTileY - R; TileY <= CenterTileY + R; TileY++) {
        for (auto TileX = CenterTileX - R; TileX <= CenterTileX + R; TileX++) {
          auto DX = TileX - CenterTileX;
          auto DY = TileY - CenterTileY;

          if (DX * DX + DY * DY >= R * R)
            continue;
          if (TileX < 0 || TileY < 0 || TileX >= MapArea->Size ||
              TileY >= MapArea->Size)
            continue;

          MapArea->Tiles[TileX][TileY].Elevation += 2;
        }
      }
    }
  }

  for (auto I = 0; I < 1000; I++) {
    auto TileX = rand() % MapArea->Size;
    auto TileY = rand() % MapArea->Size;

    MapArea->Tiles[TileX][TileY].Elevation += 2 - rand() % 5;
  }
}

void cDefaultMapGenerator::GenerateWater(cMapArea *MapArea) const {
  for (auto I = 0; I < 20; I++) {
    auto CenterTileX = rand() % MapArea->Size;
    auto CenterTileY = rand() % MapArea->Size;
    auto R = 5 + rand() % 13;

    for (auto TileY = CenterTileY - R; TileY <= CenterTileY + R; TileY++) {
      for (auto TileX = CenterTileX - R; TileX <= CenterTileX + R; TileX++) {
        auto DX = TileX - CenterTileX;
        auto DY = TileY - CenterTileY;

        if (DX * DX + DY * DY >= R * R)
          continue;
        if (TileX <= 0 || TileY <= 0 || TileX >= MapArea->Size - 1 ||
            TileY >= MapArea->Size - 1)
          continue;
        if (MapArea->Tiles[TileX][TileY].Elevation > 0)
          continue;
        if (MapArea->Tiles[TileX - 1][TileY].Elevation > 0)
          continue;
        if (MapArea->Tiles[TileX - 1][TileY - 1].Elevation > 0)
          continue;
        if (MapArea->Tiles[TileX][TileY - 1].Elevation > 0)
          continue;
        if (MapArea->Tiles[TileX + 1][TileY].Elevation > 0)
          continue;
        if (MapArea->Tiles[TileX + 1][TileY + 1].Elevation > 0)
          continue;
        if (MapArea->Tiles[TileX][TileY + 1].Elevation > 0)
          continue;
        if (MapArea->Tiles[TileX - 1][TileY + 1].Elevation > 0)
          continue;
        if (MapArea->Tiles[TileX + 1][TileY - 1].Elevation > 0)
          continue;
        if (DistToPlayerStartingPos(MapArea, TileX, TileY) <
            PlayerStartingAreaSize)
          continue;

        MapArea->Tiles[TileX][TileY].GroundType = (int)GetId("GroundtypeWater");
      }
    }
  }
}

void cDefaultMapGenerator::GenerateSand(cMapArea *MapArea) const {
  for (auto I = 0; I < 30; I++) {
    auto CenterTileX = rand() % MapArea->Size;
    auto CenterTileY = rand() % MapArea->Size;
    auto R = 4 + rand() % 5;

    for (auto I = 0; I < R; I++) {
      for (auto TileY = CenterTileY - R; TileY <= CenterTileY + R; TileY++) {
        for (auto TileX = CenterTileX - R; TileX <= CenterTileX + R; TileX++) {
          auto DX = TileX - CenterTileX;
          auto DY = TileY - CenterTileY;

          if (DX * DX + DY * DY >= R * R)
            continue;
          if (TileX <= 0 || TileY <= 0 || TileX >= MapArea->Size - 1 ||
              TileY >= MapArea->Size - 1)
            continue;
          if (MapArea->Tiles[TileX][TileY].GroundType ==
              (int)GetId("GroundtypeWater"))
            continue;
          if (MapArea->Tiles[TileX][TileY].Elevation > 5)
            continue;

          if (MapArea->Tiles[TileX - 1][TileY].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX - 1][TileY].GroundType !=
                  (int)GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX - 1][TileY - 1].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX - 1][TileY - 1].GroundType !=
                  (int)GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX][TileY - 1].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX][TileY - 1].GroundType !=
                  (int)GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX + 1][TileY - 1].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX + 1][TileY - 1].GroundType !=
                  (int)GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX + 1][TileY].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX + 1][TileY].GroundType !=
                  (int)GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX + 1][TileY + 1].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX + 1][TileY + 1].GroundType !=
                  (int)GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX][TileY + 1].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX][TileY + 1].GroundType !=
                  (int)GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX - 1][TileY + 1].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX - 1][TileY + 1].GroundType !=
                  (int)GetId("GroundtypeSand"))
            continue;

          MapArea->Tiles[TileX][TileY].GroundType = (int)GetId("GroundtypeSand");
        }
      }
    }
  }
}

void cDefaultMapGenerator::GenerateClay(cMapArea *MapArea) const {
  for (auto I = 0; I < 30; I++) {
    auto CenterTileX = rand() % MapArea->Size;
    auto CenterTileY = rand() % MapArea->Size;
    auto R = 2 + rand() % 3;

    for (auto I = 0; I < R; I++) {
      for (auto TileY = CenterTileY - R; TileY <= CenterTileY + R; TileY++) {
        for (auto TileX = CenterTileX - R; TileX <= CenterTileX + R; TileX++) {
          auto DX = TileX - CenterTileX;
          auto DY = TileY - CenterTileY;

          if (DX * DX + DY * DY >= R * R)
            continue;
          if (TileX <= 0 || TileY <= 0 || TileX >= MapArea->Size - 1 ||
              TileY >= MapArea->Size - 1)
            continue;
          if (MapArea->Tiles[TileX][TileY].GroundType !=
              (int)GetId("GroundtypeWater"))
            continue;

          if (MapArea->Tiles[TileX - 1][TileY].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX - 1][TileY].GroundType !=
                  (int)GetId("GroundtypeClay") &&
              MapArea->Tiles[TileX - 1][TileY - 1].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX - 1][TileY - 1].GroundType !=
                  GetId("GroundtypeClay") &&
              MapArea->Tiles[TileX][TileY - 1].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX][TileY - 1].GroundType !=
                  (int)GetId("Gr(int)oundtypeClay") &&
              MapArea->Tiles[TileX + 1][TileY - 1].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX + 1][TileY - 1].GroundType !=
                  (int)GetId("GroundtypeClay") &&
              MapArea->Tiles[TileX + 1][TileY].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX + 1][TileY].GroundType !=
                  (int)GetId("GroundtypeClay") &&
              MapArea->Tiles[TileX + 1][TileY + 1].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX + 1][TileY + 1].GroundType !=
                  (int)GetId("GroundtypeClay") &&
              MapArea->Tiles[TileX][TileY + 1].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX][TileY + 1].GroundType !=
                  (int)GetId("GroundtypeClay") &&
              MapArea->Tiles[TileX - 1][TileY + 1].GroundType !=
                  (int)GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX - 1][TileY + 1].GroundType !=
                  (int)GetId("GroundtypeClay"))
            continue;

          MapArea->Tiles[TileX][TileY].GroundType = (int)GetId("GroundtypeClay");
        }
      }
    }
  }
}

void cDefaultMapGenerator::GenerateRock(cMapArea *MapArea) const {
  for (auto I = 0; I < 10; I++) {
    auto CenterTileX = rand() % MapArea->Size;
    auto CenterTileY = rand() % MapArea->Size;
    auto R = 5 + rand() % 13;

    for (auto TileY = CenterTileY - R; TileY <= CenterTileY + R; TileY++) {
      for (auto TileX = CenterTileX - R; TileX <= CenterTileX + R; TileX++) {
        auto DX = TileX - CenterTileX;
        auto DY = TileY - CenterTileY;

        if (DX * DX + DY * DY >= R * R)
          continue;
        if (TileX < 0 || TileY < 0 || TileX >= MapArea->Size ||
            TileY >= MapArea->Size)
          continue;
        if (MapArea->Tiles[TileX][TileY].Elevation < 4)
          continue;

        MapArea->Tiles[TileX][TileY].GroundType = (int)GetId("GroundtypeRock");
      }
    }
  }
}

void cDefaultMapGenerator::GenerateTrees(cMapArea *MapArea) const {
  for (auto I = 0; I < 30; I++) {
    auto TileX = rand() % MapArea->Size;
    auto TileY = rand() % MapArea->Size;
    auto NumTrees = 15 + rand() % 15;

    for (auto J = 0; J < NumTrees; J++) {
      if (TileX >= 0 && TileY >= 0 && TileX < MapArea->Size &&
          TileY < MapArea->Size) {
        if (DistToPlayerStartingPos(MapArea, TileX, TileY) <
            PlayerStartingAreaSize)
          continue;

        if (MapArea->Tiles[TileX][TileY].GroundType ==
            (int)GetId("GroundtypeGrass"))
          if (MapArea->Tiles[TileX][TileY].Objects.size() == 0)
            MapArea->Tiles[TileX][TileY].Objects.push_back(
                MakeUPtr<cObject>("ObjectTree1"));
      }

      TileX += rand() % 7 - rand() % 7;
      TileY += rand() % 7 - rand() % 7;
    }
  }
  for (auto I = 0; I < 30; I++) {
    auto TileX = rand() % MapArea->Size;
    auto TileY = rand() % MapArea->Size;
    auto NumTrees = 15 + rand() % 15;

    for (auto J = 0; J < NumTrees; J++) {
      if (TileX >= 0 && TileY >= 0 && TileX < MapArea->Size &&
          TileY < MapArea->Size) {
        if (DistToPlayerStartingPos(MapArea, TileX, TileY) <
            PlayerStartingAreaSize)
          continue;

        if (MapArea->Tiles[TileX][TileY].GroundType ==
            (int)GetId("GroundtypeGrass"))
          if (MapArea->Tiles[TileX][TileY].Objects.size() == 0)
            MapArea->Tiles[TileX][TileY].Objects.push_back(
                MakeUPtr<cObject>("ObjectTree2"));
      }

      TileX += rand() % 7 - rand() % 7;
      TileY += rand() % 7 - rand() % 7;
    }
  }
}

void cDefaultMapGenerator::GenerateBushes(cMapArea *MapArea) const {
  for (auto I = 0; I < 200; I++) {
    auto TileX = rand() % MapArea->Size;
    auto TileY = rand() % MapArea->Size;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < PlayerStartingAreaSize)
      continue;

    if (MapArea->Tiles[TileX][TileY].GroundType == (int)GetId("GroundtypeGrass"))
      if (MapArea->Tiles[TileX][TileY].Objects.size() == 0)
        MapArea->Tiles[TileX][TileY].Objects.push_back(
            MakeUPtr<cObject>("ObjectBush1"));
  }
}

void cDefaultMapGenerator::GenerateSmallStones(cMapArea *MapArea) const {
  for (auto I = 0; I < 200; I++) {
    auto TileX = rand() % MapArea->Size;
    auto TileY = rand() % MapArea->Size;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < PlayerStartingAreaSize)
      continue;

    if (MapArea->Tiles[TileX][TileY].GroundType != (int)GetId("GroundtypeWater"))
      if (MapArea->Tiles[TileX][TileY].Objects.size() == 0)
        MapArea->Tiles[TileX][TileY].Objects.push_back(
            MakeUPtr<cObject>("ObjectSmallStone"));
  }
}

void cDefaultMapGenerator::GeneratePinkFlowers(cMapArea *MapArea) const {
  for (auto I = 0; I < 100; I++) {
    auto TileX = rand() % MapArea->Size;
    auto TileY = rand() % MapArea->Size;

    if (MapArea->Tiles[TileX][TileY].GroundType == (int)GetId("GroundtypeGrass"))
      if (MapArea->Tiles[TileX][TileY].Objects.size() == 0)
        MapArea->Tiles[TileX][TileY].Objects.push_back(
            MakeUPtr<cObject>("ObjectPinkFlower"));
  }
}

int cDefaultMapGenerator::DistToPlayerStartingPos(cMapArea *MapArea, int TileX,
                                                  int TileY) const {
  auto DX = MapArea->PlayerSpawnPosition.X - TileX;
  auto DY = MapArea->PlayerSpawnPosition.Y - TileY;
  auto Distance = std::sqrt(DX * DX + DY * DY);

  return (int)Distance;
}

void cDefaultMapGenerator::GenerateMobs(cMapArea *MapArea) const {
  for (auto I = 0; I < 200; I++) {
    auto TileX = rand() % MapArea->Size;
    auto TileY = rand() % MapArea->Size;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < PlayerStartingAreaSize)
      continue;

    if (MapArea->Tiles[TileX][TileY].GroundType !=
            (int)GetId("GroundtypeWater") &&
        MapArea->Tiles[TileX][TileY].Mob == nullptr) {
      MapArea->Tiles[TileX][TileY].Mob =
          std::make_unique<cMob>((float)TileX, (float)TileY);
      MapArea->MobsMirror.push_back(std::ref(MapArea->Tiles[TileX][TileY].Mob));
    }
  }
}

void cDefaultMapGenerator::GenerateQuestCaves(const cEngine &Engine,
                                              cMapArea *MapArea,
                                              const UPtr<cWorldMap> &WorldMap) const {

  cQuestCaveMapGenerator QuestCaveMapGenerator;

  for (auto Floor = -1; Floor >= -20; Floor--) {
    auto TileX = rand() % 94 + 3;
    auto TileY = rand() % 94 + 3;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < PlayerStartingAreaSize)
      continue;

    if (MapArea->Tiles[TileX][TileY].GroundType !=
        (int)GetId("GroundtypeWater")) {
      MapArea->Tiles[TileX][TileY].Objects.push_back(
          MakeUPtr<cObject>("ObjectQuestCaveEntrance"));
      MapArea->Tiles[TileX][TileY].WarpToFloor = Floor;

      WorldMap->MapAreas[MapArea->WorldCoord.X][MapArea->WorldCoord.Y][Floor] =
          std::make_unique<cMapArea>(Engine, WorldMap->MapAreaSize,
                                     MapArea->WorldCoord.X, MapArea->WorldCoord.Y,
                                     Floor);

      auto &quest_cave_map_area =
          WorldMap->MapAreas[MapArea->WorldCoord.X][MapArea->WorldCoord.Y][Floor];

      QuestCaveMapGenerator.GenerateQuestCaveMapArea(quest_cave_map_area.get(),
                                                     {TileX, TileY});
    }
  }
}

}  // namespace Forradia
