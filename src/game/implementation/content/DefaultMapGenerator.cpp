// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "DefaultMapGenerator.h"
#include "QuestCaveMapGenerator.h"
#include "../engine/PlanetWorldMap.h"
#include "framework/world_structure/Object.h"

namespace Forradia {

void
cDefaultMapGenerator::GenerateMapArea(
        int WorldX, int WorldY, int WorldZ) const {
  worldMap->areas[WorldX][WorldY][WorldZ] =
      MakeUPtr<cMapArea>(engine, worldMap->mapAreaSize, WorldX, WorldY, WorldZ);

  auto MapArea = worldMap->areas[WorldX][WorldY][WorldZ].get();

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
  GenerateTallGrass(MapArea);
  GenerateMobs(MapArea);
  GenerateQuestCaves(engine, MapArea, worldMap);
}

void
cDefaultMapGenerator::ClearToGrass(cMapArea *MapArea) const {
  for (auto TileY = 0; TileY < MapArea->size; TileY++)
    for (auto TileX = 0; TileX < MapArea->size; TileX++)

      MapArea->tiles[TileX][TileY].groundType = GetId("GroundTypeGrass");
}

void
cDefaultMapGenerator::GeneratePlayerStartingPosition
(cMapArea *MapArea) const {
  MapArea->spawnPos.x = static_cast<float>(
              random.Next() % MapArea->size);
  MapArea->spawnPos.y = static_cast<float>(
              random.Next() % MapArea->size);
}

void
cDefaultMapGenerator::GenerateElevation(cMapArea *MapArea) const {
  for (auto I = 0; I < 40; I++) {
    auto CenterTileX = random.Next() % MapArea->size;
    auto CenterTileY = random.Next() % MapArea->size;
    auto MaxR = 4 + random.Next() % 12;

    for (auto R = MaxR; R >= 0; R--) {
      for (auto TileY = CenterTileY - R; TileY <= CenterTileY + R; TileY++) {
        for (auto TileX = CenterTileX - R; TileX <= CenterTileX + R; TileX++) {
          auto DX = TileX - CenterTileX;
          auto DY = TileY - CenterTileY;

          if (DX * DX + DY * DY >= R * R)
            continue;
          if (TileX < 0 || TileY < 0 || TileX >= MapArea->size ||
              TileY >= MapArea->size)
            continue;

          MapArea->tiles[TileX][TileY].elevation += 2;
        }
      }
    }
  }

  for (auto I = 0; I < 1000; I++) {
    auto TileX = random.Next() % MapArea->size;
    auto TileY = random.Next() % MapArea->size;

    MapArea->tiles[TileX][TileY].elevation += random.Next() % 3;
  }
}

void
cDefaultMapGenerator::GenerateWater(cMapArea *MapArea) const {
  for (auto I = 0; I < 20; I++) {
    auto CenterTileX = random.Next() % MapArea->size;
    auto CenterTileY = random.Next() % MapArea->size;
    auto R = 5 + random.Next() % 13;

    for (auto TileY = CenterTileY - R; TileY <= CenterTileY + R; TileY++) {
      for (auto TileX = CenterTileX - R; TileX <= CenterTileX + R; TileX++) {
        auto DX = TileX - CenterTileX;
        auto DY = TileY - CenterTileY;

        if (DX * DX + DY * DY >= R * R)
          continue;
        if (TileX <= 0 || TileY <= 0 || TileX >= MapArea->size - 1 ||
            TileY >= MapArea->size - 1)
          continue;
        if (MapArea->tiles[TileX][TileY].elevation > 0)
          continue;
        if (MapArea->tiles[TileX - 1][TileY].elevation > 0)
          continue;
        if (MapArea->tiles[TileX - 1][TileY - 1].elevation > 0)
          continue;
        if (MapArea->tiles[TileX][TileY - 1].elevation > 0)
          continue;
        if (MapArea->tiles[TileX + 1][TileY].elevation > 0)
          continue;
        if (MapArea->tiles[TileX + 1][TileY + 1].elevation > 0)
          continue;
        if (MapArea->tiles[TileX][TileY + 1].elevation > 0)
          continue;
        if (MapArea->tiles[TileX - 1][TileY + 1].elevation > 0)
          continue;
        if (MapArea->tiles[TileX + 1][TileY - 1].elevation > 0)
          continue;
        if (DistToPlayerStartingPos(MapArea, TileX, TileY) <
            playerStartingAreaSize)
          continue;

        MapArea->tiles[TileX][TileY].groundType = GetId("GroundTypeWater");
      }
    }
  }
}

void
cDefaultMapGenerator::GenerateSand(cMapArea *MapArea) const {
  for (auto I = 0; I < 30; I++) {
    auto CenterTileX = random.Next() % MapArea->size;
    auto CenterTileY = random.Next() % MapArea->size;
    auto R = 4 + random.Next() % 5;

    for (auto I = 0; I < R; I++) {
      for (auto TileY = CenterTileY - R; TileY <= CenterTileY + R; TileY++) {
        for (auto TileX = CenterTileX - R; TileX <= CenterTileX + R; TileX++) {
          auto DX = TileX - CenterTileX;
          auto DY = TileY - CenterTileY;

          if (DX * DX + DY * DY >= R * R)
            continue;
          if (TileX <= 0 || TileY <= 0 || TileX >= MapArea->size - 1 ||
              TileY >= MapArea->size - 1)
            continue;
          if (MapArea->tiles[TileX][TileY].groundType ==
              GetId("GroundTypeWater"))
            continue;
          if (MapArea->tiles[TileX][TileY].elevation > 5)
            continue;

          if (MapArea->tiles[TileX - 1][TileY].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX - 1][TileY].groundType !=
                  GetId("GroundTypeSand") &&
              MapArea->tiles[TileX - 1][TileY - 1].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX - 1][TileY - 1].groundType !=
                  GetId("GroundTypeSand") &&
              MapArea->tiles[TileX][TileY - 1].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX][TileY - 1].groundType !=
                  GetId("GroundTypeSand") &&
              MapArea->tiles[TileX + 1][TileY - 1].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX + 1][TileY - 1].groundType !=
                  GetId("GroundTypeSand") &&
              MapArea->tiles[TileX + 1][TileY].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX + 1][TileY].groundType !=
                  GetId("GroundTypeSand") &&
              MapArea->tiles[TileX + 1][TileY + 1].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX + 1][TileY + 1].groundType !=
                  GetId("GroundTypeSand") &&
              MapArea->tiles[TileX][TileY + 1].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX][TileY + 1].groundType !=
                  GetId("GroundTypeSand") &&
              MapArea->tiles[TileX - 1][TileY + 1].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX - 1][TileY + 1].groundType !=
                  GetId("GroundTypeSand"))
            continue;

          MapArea->tiles[TileX][TileY].groundType = GetId("GroundTypeSand");
        }
      }
    }
  }
}

void
cDefaultMapGenerator::GenerateClay(cMapArea *MapArea) const {
  for (auto I = 0; I < 30; I++) {
    auto CenterTileX = random.Next() % MapArea->size;
    auto CenterTileY = random.Next() % MapArea->size;
    auto R = 2 + random.Next() % 3;

    for (auto I = 0; I < R; I++) {
      for (auto TileY = CenterTileY - R; TileY <= CenterTileY + R; TileY++) {
        for (auto TileX = CenterTileX - R; TileX <= CenterTileX + R; TileX++) {
          auto DX = TileX - CenterTileX;
          auto DY = TileY - CenterTileY;

          if (DX * DX + DY * DY >= R * R)
            continue;
          if (TileX <= 0 || TileY <= 0 || TileX >= MapArea->size - 1 ||
              TileY >= MapArea->size - 1)
            continue;
          if (MapArea->tiles[TileX][TileY].groundType !=
              GetId("GroundTypeWater"))
            continue;

          if (MapArea->tiles[TileX - 1][TileY].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX - 1][TileY].groundType !=
                  GetId("GroundTypeClay") &&
              MapArea->tiles[TileX - 1][TileY - 1].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX - 1][TileY - 1].groundType !=
                  GetId("GroundTypeClay") &&
              MapArea->tiles[TileX][TileY - 1].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX][TileY - 1].groundType !=
                  GetId("GroundTypeClay") &&
              MapArea->tiles[TileX + 1][TileY - 1].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX + 1][TileY - 1].groundType !=
                  GetId("GroundTypeClay") &&
              MapArea->tiles[TileX + 1][TileY].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX + 1][TileY].groundType !=
                  GetId("GroundTypeClay") &&
              MapArea->tiles[TileX + 1][TileY + 1].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX + 1][TileY + 1].groundType !=
                  GetId("GroundTypeClay") &&
              MapArea->tiles[TileX][TileY + 1].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX][TileY + 1].groundType !=
                  GetId("GroundTypeClay") &&
              MapArea->tiles[TileX - 1][TileY + 1].groundType !=
                  GetId("GroundTypeWater") &&
              MapArea->tiles[TileX - 1][TileY + 1].groundType !=
                  GetId("GroundTypeClay"))
            continue;

          MapArea->tiles[TileX][TileY].groundType = GetId("GroundTypeClay");
        }
      }
    }
  }
}

void
cDefaultMapGenerator::GenerateRock(cMapArea *MapArea) const {
  for (auto I = 0; I < 10; I++) {
    auto CenterTileX = random.Next() % MapArea->size;
    auto CenterTileY = random.Next() % MapArea->size;
    auto R = 5 + random.Next() % 13;

    for (auto TileY = CenterTileY - R; TileY <= CenterTileY + R; TileY++) {
      for (auto TileX = CenterTileX - R; TileX <= CenterTileX + R; TileX++) {
        auto DX = TileX - CenterTileX;
        auto DY = TileY - CenterTileY;

        if (DX * DX + DY * DY >= R * R)
          continue;
        if (TileX < 0 || TileY < 0 || TileX >= MapArea->size ||
            TileY >= MapArea->size)
          continue;
        if (MapArea->tiles[TileX][TileY].elevation < 4)
          continue;

        MapArea->tiles[TileX][TileY].groundType = GetId("GroundTypeRock");
      }
    }
  }
}

void
cDefaultMapGenerator::GenerateTrees(cMapArea *MapArea) const {
  for (auto I = 0; I < 30; I++) {
    auto TileX = random.Next() % MapArea->size;
    auto TileY = random.Next() % MapArea->size;
    auto NumTrees = 15 + random.Next() % 15;

    for (auto J = 0; J < NumTrees; J++) {
      if (TileX >= 0 && TileY >= 0 && TileX < MapArea->size &&
          TileY < MapArea->size) {
        if (DistToPlayerStartingPos(MapArea, TileX, TileY) <
            playerStartingAreaSize)
          continue;

        if (MapArea->tiles[TileX][TileY].groundType ==
            GetId("GroundTypeGrass"))
          if (MapArea->tiles[TileX][TileY].objects.size() == 0)
            MapArea->tiles[TileX][TileY].objects.push_back(
                MakeSPtr<cObject>("ObjectTree1"));
      }

      TileX += random.Next() % 7 - random.Next() % 7;
      TileY += random.Next() % 7 - random.Next() % 7;
    }
  }
  for (auto I = 0; I < 30; I++) {
    auto TileX = random.Next() % MapArea->size;
    auto TileY = random.Next() % MapArea->size;
    auto NumTrees = 15 + random.Next() % 15;

    for (auto J = 0; J < NumTrees; J++) {
      if (TileX >= 0 && TileY >= 0 && TileX < MapArea->size &&
          TileY < MapArea->size) {
        if (DistToPlayerStartingPos(MapArea, TileX, TileY) <
            playerStartingAreaSize)
          continue;

        if (MapArea->tiles[TileX][TileY].groundType ==
            GetId("GroundTypeGrass"))
          if (MapArea->tiles[TileX][TileY].objects.size() == 0)
            MapArea->tiles[TileX][TileY].objects.push_back(
                MakeSPtr<cObject>("ObjectTree2"));
      }

      TileX += random.Next() % 7 - random.Next() % 7;
      TileY += random.Next() % 7 - random.Next() % 7;
    }
  }
}

void
cDefaultMapGenerator::GenerateBushes(cMapArea *MapArea) const {
  for (auto I = 0; I < 200; I++) {
    auto TileX = random.Next() % MapArea->size;
    auto TileY = random.Next() % MapArea->size;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < playerStartingAreaSize)
      continue;

    if (MapArea->tiles[TileX][TileY].groundType == GetId("GroundTypeGrass"))
      if (MapArea->tiles[TileX][TileY].objects.size() == 0)
        MapArea->tiles[TileX][TileY].objects.push_back(
            MakeSPtr<cObject>("ObjectBush1"));
  }
}

void
cDefaultMapGenerator::GenerateSmallStones(cMapArea *MapArea) const {
  for (auto I = 0; I < 200; I++) {
    auto TileX = random.Next() % MapArea->size;
    auto TileY = random.Next() % MapArea->size;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < playerStartingAreaSize)
      continue;

    if (MapArea->tiles[TileX][TileY].groundType != GetId("GroundTypeWater"))
      if (MapArea->tiles[TileX][TileY].objects.size() == 0)
        MapArea->tiles[TileX][TileY].objects.push_back(
            MakeSPtr<cObject>("ObjectSmallStone"));
  }
}

void
cDefaultMapGenerator::GeneratePinkFlowers(cMapArea *MapArea) const {
  for (auto I = 0; I < 100; I++) {
    auto TileX = random.Next() % MapArea->size;
    auto TileY = random.Next() % MapArea->size;

    if (MapArea->tiles[TileX][TileY].groundType == GetId("GroundTypeGrass"))
      if (MapArea->tiles[TileX][TileY].objects.size() == 0)
        MapArea->tiles[TileX][TileY].objects.push_back(
            MakeSPtr<cObject>("ObjectPinkFlower"));
  }
}

void
cDefaultMapGenerator::GenerateTallGrass(cMapArea *MapArea) const {
  for (auto I = 0; I < 1000; I++) {
    auto TileX = random.Next() % MapArea->size;
    auto TileY = random.Next() % MapArea->size;

    if (MapArea->tiles[TileX][TileY].groundType == GetId("GroundTypeGrass"))
      if (MapArea->tiles[TileX][TileY].objects.size() == 0)
        MapArea->tiles[TileX][TileY].objects.push_back(
            MakeSPtr<cObject>("ObjectTallGrass"));
  }
}

int
cDefaultMapGenerator::DistToPlayerStartingPos(cMapArea *MapArea, int TileX,
                                                  int TileY) const {
  auto DX = MapArea->spawnPos.x - TileX;
  auto DY = MapArea->spawnPos.y - TileY;
  auto Distance = std::sqrt(DX * DX + DY * DY);

  return static_cast<int>(Distance);
}

void
cDefaultMapGenerator::GenerateMobs(cMapArea *MapArea) const {
  for (auto I = 0; I < 200; I++) {
    auto TileX = random.Next() % MapArea->size;
    auto TileY = random.Next() % MapArea->size;

    if (TileX == static_cast<int>(MapArea->spawnPos.x)
            && TileY == static_cast<int>(MapArea->spawnPos.y))
        continue;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < playerStartingAreaSize)
      continue;

    if (MapArea->tiles[TileX][TileY].groundType !=
            GetId("GroundTypeWater") &&
        MapArea->tiles[TileX][TileY].actor == nullptr) {
      MapArea->tiles[TileX][TileY].actor =
          std::make_unique<cMob>(engine,
                                 static_cast<float>(TileX),
                                 static_cast<float>(TileY),
                                 "MobRabbit");
      MapArea->mobActorsMirror.push_back(
                  std::ref(MapArea->tiles[TileX][TileY].actor));
    }
  }

  for (auto I = 0; I < 200; I++) {
    auto TileX = random.Next() % MapArea->size;
    auto TileY = random.Next() % MapArea->size;

    if (TileX == static_cast<int>(MapArea->spawnPos.x)
            && TileY == static_cast<int>(MapArea->spawnPos.y))
        continue;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < playerStartingAreaSize)
      continue;

    if (MapArea->tiles[TileX][TileY].groundType !=
            GetId("GroundTypeWater") &&
        MapArea->tiles[TileX][TileY].actor == nullptr) {
      MapArea->tiles[TileX][TileY].actor =
          std::make_unique<cMob>(engine,
                                 static_cast<float>(TileX),
                                 static_cast<float>(TileY),
                                 "MobRat");
      MapArea->mobActorsMirror.push_back(
                  std::ref(MapArea->tiles[TileX][TileY].actor));
    }
  }
}

void
cDefaultMapGenerator::
GenerateQuestCaves(const iEngine &Engine,
                   cMapArea *MapArea,
                   const UPtr<cPlanetWorldMap>&WorldMap) const {
  cQuestCaveMapGenerator QuestCaveMapGenerator;

  for (auto Floor = -1; Floor >= -20; Floor--) {
    auto TileX = random.Next() % 94 + 3;
    auto TileY = random.Next() % 94 + 3;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < playerStartingAreaSize)
      continue;

    if (MapArea->tiles[TileX][TileY].groundType !=
        GetId("GroundTypeWater")) {
      MapArea->tiles[TileX][TileY].objects.push_back(
          MakeSPtr<cObject>("ObjectQuestCaveEntrance"));
      //MapArea->Tiles[TileX][TileY].WarpToFloor = Floor;
      MapArea->tiles[TileX][TileY].properties["WarpToFloor"] = std::to_string(Floor);

      WorldMap->areas[MapArea->worldCoord.x][MapArea->worldCoord.y][Floor] =
          std::make_unique<cMapArea>(Engine, WorldMap->mapAreaSize,
                                     MapArea->worldCoord.x,
                                     MapArea->worldCoord.y,
                                     Floor);

      auto &quest_cave_map_area =
          WorldMap->areas
              [MapArea->worldCoord.x][MapArea->worldCoord.y][Floor];

      QuestCaveMapGenerator.GenerateQuestCaveMapArea(
                  quest_cave_map_area.get(),
                  {TileX, TileY});
    }
  }
}

}  // namespace Forradia
