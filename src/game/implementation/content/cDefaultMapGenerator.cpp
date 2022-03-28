// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "cDefaultMapGenerator.h"
#include "cQuestCaveMapGenerator.h"
#include "framework/world_structure/cWorldMap.h"

namespace Forradia {

void
cDefaultMapGenerator::GenerateMapArea(
        int WorldX, int WorldY, int WorldZ) const {
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

void
cDefaultMapGenerator::ClearToGrass(cMapArea *MapArea) const {
  for (auto TileY = 0; TileY < MapArea->Size; TileY++)
    for (auto TileX = 0; TileX < MapArea->Size; TileX++)

      MapArea->Tiles[TileX][TileY].GroundType = GetId("GroundtypeGrass");
}

void
cDefaultMapGenerator::GeneratePlayerStartingPosition
(cMapArea *MapArea) const {
  MapArea->PlayerSpawnPosition.X = static_cast<float>(
              Random.Next() % MapArea->Size);
  MapArea->PlayerSpawnPosition.Y = static_cast<float>(
              Random.Next() % MapArea->Size);
}

void
cDefaultMapGenerator::GenerateElevation(cMapArea *MapArea) const {
  for (auto I = 0; I < 40; I++) {
    auto CenterTileX = Random.Next() % MapArea->Size;
    auto CenterTileY = Random.Next() % MapArea->Size;
    auto MaxR = 4 + Random.Next() % 12;

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
    auto TileX = Random.Next() % MapArea->Size;
    auto TileY = Random.Next() % MapArea->Size;

    MapArea->Tiles[TileX][TileY].Elevation += Random.Next() % 3;
  }
}

void
cDefaultMapGenerator::GenerateWater(cMapArea *MapArea) const {
  for (auto I = 0; I < 20; I++) {
    auto CenterTileX = Random.Next() % MapArea->Size;
    auto CenterTileY = Random.Next() % MapArea->Size;
    auto R = 5 + Random.Next() % 13;

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

        MapArea->Tiles[TileX][TileY].GroundType = GetId("GroundtypeWater");
      }
    }
  }
}

void
cDefaultMapGenerator::GenerateSand(cMapArea *MapArea) const {
  for (auto I = 0; I < 30; I++) {
    auto CenterTileX = Random.Next() % MapArea->Size;
    auto CenterTileY = Random.Next() % MapArea->Size;
    auto R = 4 + Random.Next() % 5;

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
              GetId("GroundtypeWater"))
            continue;
          if (MapArea->Tiles[TileX][TileY].Elevation > 5)
            continue;

          if (MapArea->Tiles[TileX - 1][TileY].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX - 1][TileY].GroundType !=
                  GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX - 1][TileY - 1].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX - 1][TileY - 1].GroundType !=
                  GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX][TileY - 1].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX][TileY - 1].GroundType !=
                  GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX + 1][TileY - 1].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX + 1][TileY - 1].GroundType !=
                  GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX + 1][TileY].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX + 1][TileY].GroundType !=
                  GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX + 1][TileY + 1].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX + 1][TileY + 1].GroundType !=
                  GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX][TileY + 1].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX][TileY + 1].GroundType !=
                  GetId("GroundtypeSand") &&
              MapArea->Tiles[TileX - 1][TileY + 1].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX - 1][TileY + 1].GroundType !=
                  GetId("GroundtypeSand"))
            continue;

          MapArea->Tiles[TileX][TileY].GroundType = GetId("GroundtypeSand");
        }
      }
    }
  }
}

void
cDefaultMapGenerator::GenerateClay(cMapArea *MapArea) const {
  for (auto I = 0; I < 30; I++) {
    auto CenterTileX = Random.Next() % MapArea->Size;
    auto CenterTileY = Random.Next() % MapArea->Size;
    auto R = 2 + Random.Next() % 3;

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
              GetId("GroundtypeWater"))
            continue;

          if (MapArea->Tiles[TileX - 1][TileY].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX - 1][TileY].GroundType !=
                  GetId("GroundtypeClay") &&
              MapArea->Tiles[TileX - 1][TileY - 1].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX - 1][TileY - 1].GroundType !=
                  GetId("GroundtypeClay") &&
              MapArea->Tiles[TileX][TileY - 1].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX][TileY - 1].GroundType !=
                  GetId("Gr(int)oundtypeClay") &&
              MapArea->Tiles[TileX + 1][TileY - 1].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX + 1][TileY - 1].GroundType !=
                  GetId("GroundtypeClay") &&
              MapArea->Tiles[TileX + 1][TileY].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX + 1][TileY].GroundType !=
                  GetId("GroundtypeClay") &&
              MapArea->Tiles[TileX + 1][TileY + 1].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX + 1][TileY + 1].GroundType !=
                  GetId("GroundtypeClay") &&
              MapArea->Tiles[TileX][TileY + 1].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX][TileY + 1].GroundType !=
                  GetId("GroundtypeClay") &&
              MapArea->Tiles[TileX - 1][TileY + 1].GroundType !=
                  GetId("GroundtypeWater") &&
              MapArea->Tiles[TileX - 1][TileY + 1].GroundType !=
                  GetId("GroundtypeClay"))
            continue;

          MapArea->Tiles[TileX][TileY].GroundType = GetId("GroundtypeClay");
        }
      }
    }
  }
}

void
cDefaultMapGenerator::GenerateRock(cMapArea *MapArea) const {
  for (auto I = 0; I < 10; I++) {
    auto CenterTileX = Random.Next() % MapArea->Size;
    auto CenterTileY = Random.Next() % MapArea->Size;
    auto R = 5 + Random.Next() % 13;

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

        MapArea->Tiles[TileX][TileY].GroundType = GetId("GroundtypeRock");
      }
    }
  }
}

void
cDefaultMapGenerator::GenerateTrees(cMapArea *MapArea) const {
  for (auto I = 0; I < 30; I++) {
    auto TileX = Random.Next() % MapArea->Size;
    auto TileY = Random.Next() % MapArea->Size;
    auto NumTrees = 15 + Random.Next() % 15;

    for (auto J = 0; J < NumTrees; J++) {
      if (TileX >= 0 && TileY >= 0 && TileX < MapArea->Size &&
          TileY < MapArea->Size) {
        if (DistToPlayerStartingPos(MapArea, TileX, TileY) <
            PlayerStartingAreaSize)
          continue;

        if (MapArea->Tiles[TileX][TileY].GroundType ==
            GetId("GroundtypeGrass"))
          if (MapArea->Tiles[TileX][TileY].Objects.size() == 0)
            MapArea->Tiles[TileX][TileY].Objects.push_back(
                MakeUPtr<cObject>("ObjectTree1"));
      }

      TileX += Random.Next() % 7 - Random.Next() % 7;
      TileY += Random.Next() % 7 - Random.Next() % 7;
    }
  }
  for (auto I = 0; I < 30; I++) {
    auto TileX = Random.Next() % MapArea->Size;
    auto TileY = Random.Next() % MapArea->Size;
    auto NumTrees = 15 + Random.Next() % 15;

    for (auto J = 0; J < NumTrees; J++) {
      if (TileX >= 0 && TileY >= 0 && TileX < MapArea->Size &&
          TileY < MapArea->Size) {
        if (DistToPlayerStartingPos(MapArea, TileX, TileY) <
            PlayerStartingAreaSize)
          continue;

        if (MapArea->Tiles[TileX][TileY].GroundType ==
            GetId("GroundtypeGrass"))
          if (MapArea->Tiles[TileX][TileY].Objects.size() == 0)
            MapArea->Tiles[TileX][TileY].Objects.push_back(
                MakeUPtr<cObject>("ObjectTree2"));
      }

      TileX += Random.Next() % 7 - Random.Next() % 7;
      TileY += Random.Next() % 7 - Random.Next() % 7;
    }
  }
}

void
cDefaultMapGenerator::GenerateBushes(cMapArea *MapArea) const {
  for (auto I = 0; I < 200; I++) {
    auto TileX = Random.Next() % MapArea->Size;
    auto TileY = Random.Next() % MapArea->Size;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < PlayerStartingAreaSize)
      continue;

    if (MapArea->Tiles[TileX][TileY].GroundType == GetId("GroundtypeGrass"))
      if (MapArea->Tiles[TileX][TileY].Objects.size() == 0)
        MapArea->Tiles[TileX][TileY].Objects.push_back(
            MakeUPtr<cObject>("ObjectBush1"));
  }
}

void
cDefaultMapGenerator::GenerateSmallStones(cMapArea *MapArea) const {
  for (auto I = 0; I < 200; I++) {
    auto TileX = Random.Next() % MapArea->Size;
    auto TileY = Random.Next() % MapArea->Size;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < PlayerStartingAreaSize)
      continue;

    if (MapArea->Tiles[TileX][TileY].GroundType != GetId("GroundtypeWater"))
      if (MapArea->Tiles[TileX][TileY].Objects.size() == 0)
        MapArea->Tiles[TileX][TileY].Objects.push_back(
            MakeUPtr<cObject>("ObjectSmallStone"));
  }
}

void
cDefaultMapGenerator::GeneratePinkFlowers(cMapArea *MapArea) const {
  for (auto I = 0; I < 100; I++) {
    auto TileX = Random.Next() % MapArea->Size;
    auto TileY = Random.Next() % MapArea->Size;

    if (MapArea->Tiles[TileX][TileY].GroundType == GetId("GroundtypeGrass"))
      if (MapArea->Tiles[TileX][TileY].Objects.size() == 0)
        MapArea->Tiles[TileX][TileY].Objects.push_back(
            MakeUPtr<cObject>("ObjectPinkFlower"));
  }
}

int
cDefaultMapGenerator::DistToPlayerStartingPos(cMapArea *MapArea, int TileX,
                                                  int TileY) const {
  auto DX = MapArea->PlayerSpawnPosition.X - TileX;
  auto DY = MapArea->PlayerSpawnPosition.Y - TileY;
  auto Distance = std::sqrt(DX * DX + DY * DY);

  return static_cast<int>(Distance);
}

void
cDefaultMapGenerator::GenerateMobs(cMapArea *MapArea) const {
  for (auto I = 0; I < 200; I++) {
    auto TileX = Random.Next() % MapArea->Size;
    auto TileY = Random.Next() % MapArea->Size;

    if (TileX == static_cast<int>(MapArea->PlayerSpawnPosition.X)
            && TileY == static_cast<int>(MapArea->PlayerSpawnPosition.Y))
        continue;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < PlayerStartingAreaSize)
      continue;

    if (MapArea->Tiles[TileX][TileY].GroundType !=
            GetId("GroundtypeWater") &&
        MapArea->Tiles[TileX][TileY].Actor == nullptr) {
      MapArea->Tiles[TileX][TileY].Actor =
          std::make_unique<cMob>(Engine,
                                 static_cast<float>(TileX),
                                 static_cast<float>(TileY),
                                 "MobRabbit");
      MapArea->ActorsMirror.push_back(std::ref(MapArea->Tiles[TileX][TileY].Actor));
    }
  }

  for (auto I = 0; I < 200; I++) {
    auto TileX = Random.Next() % MapArea->Size;
    auto TileY = Random.Next() % MapArea->Size;

    if (TileX == static_cast<int>(MapArea->PlayerSpawnPosition.X)
            && TileY == static_cast<int>(MapArea->PlayerSpawnPosition.Y))
        continue;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < PlayerStartingAreaSize)
      continue;

    if (MapArea->Tiles[TileX][TileY].GroundType !=
            GetId("GroundtypeWater") &&
        MapArea->Tiles[TileX][TileY].Actor == nullptr) {
      MapArea->Tiles[TileX][TileY].Actor =
          std::make_unique<cMob>(Engine,
                                 static_cast<float>(TileX),
                                 static_cast<float>(TileY),
                                 "MobRat");
      MapArea->ActorsMirror.push_back(std::ref(MapArea->Tiles[TileX][TileY].Actor));
    }
  }
}

void
cDefaultMapGenerator::
GenerateQuestCaves(const iEngine &Engine,
                   cMapArea *MapArea,
                   const UPtr<cWorldMap>&WorldMap) const {
  cQuestCaveMapGenerator QuestCaveMapGenerator;

  for (auto Floor = -1; Floor >= -20; Floor--) {
    auto TileX = Random.Next() % 94 + 3;
    auto TileY = Random.Next() % 94 + 3;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < PlayerStartingAreaSize)
      continue;

    if (MapArea->Tiles[TileX][TileY].GroundType !=
        GetId("GroundtypeWater")) {
      MapArea->Tiles[TileX][TileY].Objects.push_back(
          MakeUPtr<cObject>("ObjectQuestCaveEntrance"));
      MapArea->Tiles[TileX][TileY].WarpToFloor = Floor;

      WorldMap->MapAreas[MapArea->WorldCoord.X][MapArea->WorldCoord.Y][Floor] =
          std::make_unique<cMapArea>(Engine, WorldMap->MapAreaSize,
                                     MapArea->WorldCoord.X,
                                     MapArea->WorldCoord.Y,
                                     Floor);

      auto &quest_cave_map_area =
          WorldMap->MapAreas
              [MapArea->WorldCoord.X][MapArea->WorldCoord.Y][Floor];

      QuestCaveMapGenerator.GenerateQuestCaveMapArea(
                  quest_cave_map_area.get(),
                  {TileX, TileY});
    }
  }
}

}  // namespace Forradia
