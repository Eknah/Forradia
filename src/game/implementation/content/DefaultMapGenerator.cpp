// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "DefaultMapGenerator.h"
#include "QuestCaveMapGenerator.h"
#include "../engine/PlanetWorldMap.h"
#include "framework/worldStructure/Object.h"

namespace Forradia {

void
DefaultMapGenerator::GenerateMapArea(
        int worldx, int worldy, int worldZ) const {
  worldMap->areas[worldx][worldy][worldZ] =
      MakeUPtr<MapArea>(e, worldMap->mapAreaSize, worldx, worldy, worldZ);

  auto mapArea = worldMap->areas[worldx][worldy][worldZ].get();

  ClearToGrass(mapArea);
  GeneratePlayerStartingPosition(mapArea);
  GenerateElevation(mapArea);
  GenerateWater(mapArea);
  GenerateSand(mapArea);
  GenerateClay(mapArea);
  GenerateRock(mapArea);
  GenerateTrees(mapArea);
  GenerateBushes(mapArea);
  GenerateSmallStones(mapArea);
  GeneratePinkFlowers(mapArea);
  GenerateTallGrass(mapArea);
  GenerateMobs(mapArea);
  GenerateQuestCaves(e, mapArea, worldMap);
}

void
DefaultMapGenerator::ClearToGrass(MapArea *mapArea) const {
  for (auto tileY = 0; tileY < mapArea->size; tileY++)
    for (auto tileX = 0; tileX < mapArea->size; tileX++)

      mapArea->tiles[tileX][tileY].groundType = GetId("GroundTypeGrass");
}

void
DefaultMapGenerator::GeneratePlayerStartingPosition
(MapArea *mapArea) const {
  mapArea->spawnPos.x = static_cast<float>(
              random.Next() % mapArea->size);
  mapArea->spawnPos.y = static_cast<float>(
              random.Next() % mapArea->size);
}

void
DefaultMapGenerator::GenerateElevation(MapArea *mapArea) const {
  for (auto i = 0; i < 40; i++) {
    auto centerTileX = random.Next() % mapArea->size;
    auto centerTileY = random.Next() % mapArea->size;
    auto maxR = 4 + random.Next() % 12;

    for (auto r = maxR; r >= 0; r--) {
      for (auto tileY = centerTileY - r; tileY <= centerTileY + r; tileY++) {
        for (auto tileX = centerTileX - r; tileX <= centerTileX + r; tileX++) {
          auto dx = tileX - centerTileX;
          auto dy = tileY - centerTileY;

          if (dx * dx + dy * dy >= r * r)
            continue;
          if (tileX < 0 || tileY < 0 || tileX >= mapArea->size ||
              tileY >= mapArea->size)
            continue;

          mapArea->tiles[tileX][tileY].elevation += 2;
        }
      }
    }
  }

  for (auto i = 0; i < 1000; i++) {
    auto tileX = random.Next() % mapArea->size;
    auto tileY = random.Next() % mapArea->size;

    mapArea->tiles[tileX][tileY].elevation += random.Next() % 3;
  }
}

void
DefaultMapGenerator::GenerateWater(MapArea *mapArea) const {
  for (auto i = 0; i < 20; i++) {
    auto centerTileX = random.Next() % mapArea->size;
    auto centerTileY = random.Next() % mapArea->size;
    auto R = 5 + random.Next() % 13;

    for (auto tileY = centerTileY - R; tileY <= centerTileY + R; tileY++) {
      for (auto tileX = centerTileX - R; tileX <= centerTileX + R; tileX++) {
        auto dx = tileX - centerTileX;
        auto dy = tileY - centerTileY;

        if (dx * dx + dy * dy >= R * R)
          continue;
        if (tileX <= 0 || tileY <= 0 || tileX >= mapArea->size - 1 ||
            tileY >= mapArea->size - 1)
          continue;
        if (mapArea->tiles[tileX][tileY].elevation > 0)
          continue;
        if (mapArea->tiles[tileX - 1][tileY].elevation > 0)
          continue;
        if (mapArea->tiles[tileX - 1][tileY - 1].elevation > 0)
          continue;
        if (mapArea->tiles[tileX][tileY - 1].elevation > 0)
          continue;
        if (mapArea->tiles[tileX + 1][tileY].elevation > 0)
          continue;
        if (mapArea->tiles[tileX + 1][tileY + 1].elevation > 0)
          continue;
        if (mapArea->tiles[tileX][tileY + 1].elevation > 0)
          continue;
        if (mapArea->tiles[tileX - 1][tileY + 1].elevation > 0)
          continue;
        if (mapArea->tiles[tileX + 1][tileY - 1].elevation > 0)
          continue;
        if (DistToPlayerStartingPos(mapArea, tileX, tileY) <
            playerStartingAreaSize)
          continue;

        mapArea->tiles[tileX][tileY].groundType = GetId("GroundTypeWater");
      }
    }
  }
}

void
DefaultMapGenerator::GenerateSand(MapArea *mapArea) const {
  for (auto i = 0; i < 30; i++) {
    auto centerTileX = random.Next() % mapArea->size;
    auto centerTileY = random.Next() % mapArea->size;
    auto r = 4 + random.Next() % 5;

    for (auto j = 0; j < r; j++) {
      for (auto tileY = centerTileY - r; tileY <= centerTileY + r; tileY++) {
        for (auto tileX = centerTileX - r; tileX <= centerTileX + r; tileX++) {
          auto dx = tileX - centerTileX;
          auto dy = tileY - centerTileY;

          if (dx * dx + dy * dy >= r * r)
            continue;
          if (tileX <= 0 || tileY <= 0 || tileX >= mapArea->size - 1 ||
              tileY >= mapArea->size - 1)
            continue;
          if (mapArea->tiles[tileX][tileY].groundType ==
              GetId("GroundTypeWater"))
            continue;
          if (mapArea->tiles[tileX][tileY].elevation > 5)
            continue;

          if (mapArea->tiles[tileX - 1][tileY].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX - 1][tileY].groundType !=
                  GetId("GroundTypeSand") &&
              mapArea->tiles[tileX - 1][tileY - 1].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX - 1][tileY - 1].groundType !=
                  GetId("GroundTypeSand") &&
              mapArea->tiles[tileX][tileY - 1].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX][tileY - 1].groundType !=
                  GetId("GroundTypeSand") &&
              mapArea->tiles[tileX + 1][tileY - 1].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX + 1][tileY - 1].groundType !=
                  GetId("GroundTypeSand") &&
              mapArea->tiles[tileX + 1][tileY].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX + 1][tileY].groundType !=
                  GetId("GroundTypeSand") &&
              mapArea->tiles[tileX + 1][tileY + 1].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX + 1][tileY + 1].groundType !=
                  GetId("GroundTypeSand") &&
              mapArea->tiles[tileX][tileY + 1].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX][tileY + 1].groundType !=
                  GetId("GroundTypeSand") &&
              mapArea->tiles[tileX - 1][tileY + 1].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX - 1][tileY + 1].groundType !=
                  GetId("GroundTypeSand"))
            continue;

          mapArea->tiles[tileX][tileY].groundType = GetId("GroundTypeSand");
        }
      }
    }
  }
}

void
DefaultMapGenerator::GenerateClay(MapArea *mapArea) const {
  for (auto i = 0; i < 30; i++) {
    auto centerTileX = random.Next() % mapArea->size;
    auto centerTileY = random.Next() % mapArea->size;
    auto r = 2 + random.Next() % 3;

    for (auto j = 0; j < r; j++) {
      for (auto tileY = centerTileY - r; tileY <= centerTileY + r; tileY++) {
        for (auto tileX = centerTileX - r; tileX <= centerTileX + r; tileX++) {
          auto dx = tileX - centerTileX;
          auto dy = tileY - centerTileY;

          if (dx * dx + dy * dy >= r * r)
            continue;
          if (tileX <= 0 || tileY <= 0 || tileX >= mapArea->size - 1 ||
              tileY >= mapArea->size - 1)
            continue;
          if (mapArea->tiles[tileX][tileY].groundType !=
              GetId("GroundTypeWater"))
            continue;

          if (mapArea->tiles[tileX - 1][tileY].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX - 1][tileY].groundType !=
                  GetId("GroundTypeClay") &&
              mapArea->tiles[tileX - 1][tileY - 1].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX - 1][tileY - 1].groundType !=
                  GetId("GroundTypeClay") &&
              mapArea->tiles[tileX][tileY - 1].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX][tileY - 1].groundType !=
                  GetId("GroundTypeClay") &&
              mapArea->tiles[tileX + 1][tileY - 1].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX + 1][tileY - 1].groundType !=
                  GetId("GroundTypeClay") &&
              mapArea->tiles[tileX + 1][tileY].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX + 1][tileY].groundType !=
                  GetId("GroundTypeClay") &&
              mapArea->tiles[tileX + 1][tileY + 1].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX + 1][tileY + 1].groundType !=
                  GetId("GroundTypeClay") &&
              mapArea->tiles[tileX][tileY + 1].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX][tileY + 1].groundType !=
                  GetId("GroundTypeClay") &&
              mapArea->tiles[tileX - 1][tileY + 1].groundType !=
                  GetId("GroundTypeWater") &&
              mapArea->tiles[tileX - 1][tileY + 1].groundType !=
                  GetId("GroundTypeClay"))
            continue;

          mapArea->tiles[tileX][tileY].groundType = GetId("GroundTypeClay");
        }
      }
    }
  }
}

void
DefaultMapGenerator::GenerateRock(MapArea *mapArea) const {
  for (auto i = 0; i < 10; i++) {
    auto centerTileX = random.Next() % mapArea->size;
    auto centerTileY = random.Next() % mapArea->size;
    auto r = 5 + random.Next() % 13;

    for (auto tileY = centerTileY - r; tileY <= centerTileY + r; tileY++) {
      for (auto tileX = centerTileX - r; tileX <= centerTileX + r; tileX++) {
        auto dx = tileX - centerTileX;
        auto dy = tileY - centerTileY;

        if (dx * dx + dy * dy >= r * r)
          continue;
        if (tileX < 0 || tileY < 0 || tileX >= mapArea->size ||
            tileY >= mapArea->size)
          continue;
        if (mapArea->tiles[tileX][tileY].elevation < 4)
          continue;

        mapArea->tiles[tileX][tileY].groundType = GetId("GroundTypeRock");
      }
    }
  }
}

void
DefaultMapGenerator::GenerateTrees(MapArea *mapArea) const {
  for (auto i = 0; i < 30; i++) {
    auto tileX = random.Next() % mapArea->size;
    auto tileY = random.Next() % mapArea->size;
    auto numTrees = 15 + random.Next() % 15;

    for (auto j = 0; j < numTrees; j++) {
      if (tileX >= 0 && tileY >= 0 && tileX < mapArea->size &&
          tileY < mapArea->size) {
        if (DistToPlayerStartingPos(mapArea, tileX, tileY) <
            playerStartingAreaSize)
          continue;

        if (mapArea->tiles[tileX][tileY].groundType ==
            GetId("GroundTypeGrass"))
          if (mapArea->tiles[tileX][tileY].objects.size() == 0)
            mapArea->tiles[tileX][tileY].objects.push_back(
                MakeSPtr<Object>("ObjectTree1"));
      }

      tileX += random.Next() % 7 - random.Next() % 7;
      tileY += random.Next() % 7 - random.Next() % 7;
    }
  }
  for (auto i = 0; i < 30; i++) {
    auto tileX = random.Next() % mapArea->size;
    auto tileY = random.Next() % mapArea->size;
    auto numTrees = 15 + random.Next() % 15;

    for (auto j = 0; j < numTrees; j++) {
      if (tileX >= 0 && tileY >= 0 && tileX < mapArea->size &&
          tileY < mapArea->size) {
        if (DistToPlayerStartingPos(mapArea, tileX, tileY) <
            playerStartingAreaSize)
          continue;

        if (mapArea->tiles[tileX][tileY].groundType ==
            GetId("GroundTypeGrass"))
          if (mapArea->tiles[tileX][tileY].objects.size() == 0)
            mapArea->tiles[tileX][tileY].objects.push_back(
                MakeSPtr<Object>("ObjectTree2"));
      }

      tileX += random.Next() % 7 - random.Next() % 7;
      tileY += random.Next() % 7 - random.Next() % 7;
    }
  }
}

void
DefaultMapGenerator::GenerateBushes(MapArea *mapArea) const {
  for (auto i = 0; i < 200; i++) {
    auto tileX = random.Next() % mapArea->size;
    auto tileY = random.Next() % mapArea->size;

    if (DistToPlayerStartingPos(mapArea, tileX, tileY) < playerStartingAreaSize)
      continue;

    if (mapArea->tiles[tileX][tileY].groundType == GetId("GroundTypeGrass"))
      if (mapArea->tiles[tileX][tileY].objects.size() == 0)
        mapArea->tiles[tileX][tileY].objects.push_back(
            MakeSPtr<Object>("ObjectBush1"));
  }
}

void
DefaultMapGenerator::GenerateSmallStones(MapArea *mapArea) const {
  for (auto i = 0; i < 200; i++) {
    auto tileX = random.Next() % mapArea->size;
    auto tileY = random.Next() % mapArea->size;

    if (DistToPlayerStartingPos(mapArea, tileX, tileY) < playerStartingAreaSize)
      continue;

    if (mapArea->tiles[tileX][tileY].groundType != GetId("GroundTypeWater"))
      if (mapArea->tiles[tileX][tileY].objects.size() == 0)
        mapArea->tiles[tileX][tileY].objects.push_back(
            MakeSPtr<Object>("ObjectSmallStone"));
  }
}

void
DefaultMapGenerator::GeneratePinkFlowers(MapArea *mapArea) const {
  for (auto i = 0; i < 100; i++) {
    auto tileX = random.Next() % mapArea->size;
    auto tileY = random.Next() % mapArea->size;

    if (mapArea->tiles[tileX][tileY].groundType == GetId("GroundTypeGrass"))
      if (mapArea->tiles[tileX][tileY].objects.size() == 0)
        mapArea->tiles[tileX][tileY].objects.push_back(
            MakeSPtr<Object>("ObjectPinkFlower"));
  }
}

void
DefaultMapGenerator::GenerateTallGrass(MapArea *mapArea) const {
  for (auto i = 0; i < 1000; i++) {
    auto tileX = random.Next() % mapArea->size;
    auto tileY = random.Next() % mapArea->size;

    if (mapArea->tiles[tileX][tileY].groundType == GetId("GroundTypeGrass"))
      if (mapArea->tiles[tileX][tileY].objects.size() == 0)
        mapArea->tiles[tileX][tileY].objects.push_back(
            MakeSPtr<Object>("ObjectTallGrass"));
  }
}

int
DefaultMapGenerator::DistToPlayerStartingPos(MapArea *mapArea, int tileX,
                                                  int tileY) const {
  auto dx = mapArea->spawnPos.x - tileX;
  auto dy = mapArea->spawnPos.y - tileY;
  auto distance = std::sqrt(dx * dx + dy * dy);

  return static_cast<int>(distance);
}

void
DefaultMapGenerator::GenerateMobs(MapArea *mapArea) const {
  for (auto i = 0; i < 200; i++) {
    auto tileX = random.Next() % mapArea->size;
    auto tileY = random.Next() % mapArea->size;

    if (tileX == static_cast<int>(mapArea->spawnPos.x)
            && tileY == static_cast<int>(mapArea->spawnPos.y))
        continue;

    if (DistToPlayerStartingPos(mapArea, tileX, tileY) < playerStartingAreaSize)
      continue;

    if (mapArea->tiles[tileX][tileY].groundType !=
            GetId("GroundTypeWater") &&
        mapArea->tiles[tileX][tileY].actor == nullptr) {
      mapArea->tiles[tileX][tileY].actor =
          std::make_unique<Mob>(e,
                                 static_cast<float>(tileX),
                                 static_cast<float>(tileY),
                                 "MobRabbit");
      mapArea->mobActorsMirror.insert({mapArea->tiles[tileX][tileY].actor->actorId,
                  std::ref(mapArea->tiles[tileX][tileY].actor)});
    }
  }

  for (auto i = 0; i < 200; i++) {
    auto tileX = random.Next() % mapArea->size;
    auto tileY = random.Next() % mapArea->size;

    if (tileX == static_cast<int>(mapArea->spawnPos.x)
            && tileY == static_cast<int>(mapArea->spawnPos.y))
        continue;

    if (DistToPlayerStartingPos(mapArea, tileX, tileY) < playerStartingAreaSize)
      continue;

    if (mapArea->tiles[tileX][tileY].groundType !=
            GetId("GroundTypeWater") &&
        mapArea->tiles[tileX][tileY].actor == nullptr) {
      mapArea->tiles[tileX][tileY].actor =
          std::make_unique<Mob>(e,
                                 static_cast<float>(tileX),
                                 static_cast<float>(tileY),
                                 "MobRat");
      mapArea->mobActorsMirror.insert({mapArea->tiles[tileX][tileY].actor->actorId,
                  std::ref(mapArea->tiles[tileX][tileY].actor)});
    }
  }
}

void
DefaultMapGenerator::
GenerateQuestCaves(const IEngine &e,
                   MapArea *mapArea,
                   const UPtr<PlanetWorldMap>&worldMap) const {
  QuestCaveMapGenerator questCaveMapGenerator;

  for (auto floor = -1; floor >= -20; floor--) {
    auto tileX = random.Next() % 94 + 3;
    auto tileY = random.Next() % 94 + 3;

    if (DistToPlayerStartingPos(mapArea, tileX, tileY) < playerStartingAreaSize)
      continue;

    if (mapArea->tiles[tileX][tileY].groundType !=
        GetId("GroundTypeWater")) {
      mapArea->tiles[tileX][tileY].objects.push_back(
          MakeSPtr<Object>("ObjectQuestCaveEntrance"));
      //MapArea->Tiles[tileX][tileY].WarpToFloor = Floor;
      mapArea->tiles[tileX][tileY].properties["WarpToFloor"] = std::to_string(floor);

      worldMap->areas[mapArea->worldCoord.x][mapArea->worldCoord.y][floor] =
          std::make_unique<MapArea>(e, worldMap->mapAreaSize,
                                     mapArea->worldCoord.x,
                                     mapArea->worldCoord.y,
                                     floor);

      auto &questCaveMapArea =
          worldMap->areas
              [mapArea->worldCoord.x][mapArea->worldCoord.y][floor];

      questCaveMapGenerator.GenerateQuestCaveMapArea(
                  questCaveMapArea.get(),
                  {tileX, tileY});
    }
  }
}

}  // namespace Forradia
