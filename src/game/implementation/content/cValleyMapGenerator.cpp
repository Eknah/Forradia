// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <memory>
#include "cValleyMapGenerator.h"
#include "../engine/cPlanetWorldMap.h"
#include "framework/world_structure/cObject.h"

namespace Forradia {

void
cValleyMapGenerator::GenerateMapArea(
        int WorldX, int WorldY, int WorldZ) const {
  WorldMap->areas[WorldX][WorldY][WorldZ] =
      MakeUPtr<cMapArea>(Engine, WorldMap->mapAreaSize, WorldX, WorldY, WorldZ);

  auto MapArea = WorldMap->areas[WorldX][WorldY][WorldZ].get();

  ClearToGrass(MapArea);
  GeneratePlayerStartingPosition(MapArea);
  GenerateElevation(MapArea);
  GenerateRock(MapArea);
  GenerateTrees(MapArea);
  GenerateBushes(MapArea);
  GenerateSmallStones(MapArea);
  GeneratePinkFlowers(MapArea);
  GenerateTallGrass(MapArea);
  GenerateVillage(MapArea);
  GenerateMobs(MapArea);
}

void
cValleyMapGenerator::ClearToGrass(cMapArea *MapArea) const {
  for (auto TileY = 0; TileY < MapArea->size; TileY++)
    for (auto TileX = 0; TileX < MapArea->size; TileX++)

      MapArea->tiles[TileX][TileY].groundType = GetId("GroundTypeGrass");
}

void
cValleyMapGenerator::GeneratePlayerStartingPosition
(cMapArea *MapArea) const {
    MapArea->spawnPos = {static_cast<float>(MapArea->size/2),
                         static_cast<float>(MapArea->size/2)};
}

void
cValleyMapGenerator::GenerateElevation(cMapArea *MapArea) const {
  for (auto y = 0; y < MapArea->size; y++) {
      for (auto x = 0; x < MapArea->size; x++) {
        auto dxLeft = x;
        auto dxRight = MapArea->size - x;
        auto dyTop = y;
        auto dyBottom = MapArea->size - y;

        auto elevHorizontal = std::max(dxLeft, dxRight);
        auto elevVertical = std::max(dyTop, dyBottom);
        auto elev = std::max(std::max(elevHorizontal, elevVertical), 86)*5 - 40;

        MapArea->tiles[x][y].elevation = elev/1.5f;

      }
  }





  for (auto I = 0; I < 60; I++) {
    auto CenterTileX = 0;
    auto CenterTileY = 0;
    auto MaxR = 4 + Random.Next() % 6;

    do {
  CenterTileX = Random.Next() % MapArea->size;
  CenterTileY = Random.Next() % MapArea->size;
  MaxR = 1 + Random.Next() % 6;
    } while(std::abs(CenterTileX - MapArea->size/2) < villageSize/2
            || std::abs(CenterTileY - MapArea->size/2) < villageSize/2);

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

          MapArea->tiles[TileX][TileY].elevation += 5;
        }
      }
    }
  }



}

void
cValleyMapGenerator::GenerateRock(cMapArea *MapArea) const {
  for (auto I = 0; I < 30; I++) {

      auto CenterTileX = 0;
      auto CenterTileY = 0;
      auto R = 0;

      do {
    CenterTileX = Random.Next() % MapArea->size;
    CenterTileY = Random.Next() % MapArea->size;
    R = 5 + Random.Next() % 13;
      } while(std::abs(CenterTileX - MapArea->size/2) < villageSize/2 + R
              || std::abs(CenterTileY - MapArea->size/2) < villageSize/2 + R);


    for (auto TileY = CenterTileY - R; TileY <= CenterTileY + R; TileY++) {
      for (auto TileX = CenterTileX - R; TileX <= CenterTileX + R; TileX++) {
        auto DX = TileX - CenterTileX;
        auto DY = TileY - CenterTileY;

        if (DX * DX + DY * DY >= R * R)
          continue;
        if (TileX < 0 || TileY < 0 || TileX >= MapArea->size ||
            TileY >= MapArea->size)
          continue;
        if (MapArea->tiles[TileX][TileY].elevation < 150)
          continue;

        MapArea->tiles[TileX][TileY].groundType = GetId("GroundTypeRock");
      }
    }
  }
}

void
cValleyMapGenerator::GenerateTrees(cMapArea *MapArea) const {
  for (auto I = 0; I < 30; I++) {
    auto TileX = Random.Next() % MapArea->size;
    auto TileY = Random.Next() % MapArea->size;
    auto NumTrees = 15 + Random.Next() % 15;

    for (auto J = 0; J < NumTrees; J++) {
      if (TileX >= 0 && TileY >= 0 && TileX < MapArea->size &&
          TileY < MapArea->size) {
        if (DistToPlayerStartingPos(MapArea, TileX, TileY) <
            PlayerStartingAreaSize)
          continue;

        if (MapArea->tiles[TileX][TileY].groundType ==
            GetId("GroundTypeGrass"))
          if (MapArea->tiles[TileX][TileY].objects.size() == 0)
            MapArea->tiles[TileX][TileY].objects.push_back(
                MakeSPtr<cObject>("ObjectTree1"));
      }

      TileX += Random.Next() % 7 - Random.Next() % 7;
      TileY += Random.Next() % 7 - Random.Next() % 7;
    }
  }
  for (auto I = 0; I < 30; I++) {
    auto TileX = Random.Next() % MapArea->size;
    auto TileY = Random.Next() % MapArea->size;
    auto NumTrees = 15 + Random.Next() % 15;

    for (auto J = 0; J < NumTrees; J++) {
      if (TileX >= 0 && TileY >= 0 && TileX < MapArea->size &&
          TileY < MapArea->size) {
        if (DistToPlayerStartingPos(MapArea, TileX, TileY) <
            PlayerStartingAreaSize)
          continue;

        if (MapArea->tiles[TileX][TileY].groundType ==
            GetId("GroundTypeGrass"))
          if (MapArea->tiles[TileX][TileY].objects.size() == 0)
            MapArea->tiles[TileX][TileY].objects.push_back(
                MakeSPtr<cObject>("ObjectTree2"));
      }

      TileX += Random.Next() % 7 - Random.Next() % 7;
      TileY += Random.Next() % 7 - Random.Next() % 7;
    }
  }
}

void
cValleyMapGenerator::GenerateVillage(cMapArea *MapArea) const {

    auto xCenter = MapArea->size/2;
    auto yCenter = MapArea->size/2;
    auto xStart = xCenter - villageSize/2;
    auto yStart = xCenter - villageSize/2;
    auto xEnd = xStart + villageSize;
    auto yEnd = yStart + villageSize;

    for (auto y = yStart; y <= yEnd; y++)  {

        for (auto x = xStart; x <= xEnd; x++)  {
            //MapArea->tiles[x][y].groundType = GetId("GroundTypeTrail");
            MapArea->tiles[x][y].objects.clear();
        }
    }

    for (auto y = yCenter - 1; y <= yCenter + 1; y++)  {

        for (auto x = xCenter - 1; x <= xCenter + 1; x++)  {
            MapArea->tiles[x][y].groundType = GetId("GroundTypeCobblestone");
        }
    }

    for (auto y = 0; y < MapArea->size; y++) {
        MapArea->tiles[xCenter][y].objects.clear();
        MapArea->tiles[xCenter][y].groundType = GetId("GroundTypeTrail");
    }

    for (auto x = 0; x < MapArea->size; x++) {
        MapArea->tiles[x][yCenter].objects.clear();
        MapArea->tiles[x][yCenter].groundType = GetId("GroundTypeTrail");
    }

    for (auto y = yStart; y <= yEnd; y++)
        MapArea->tiles[xCenter][y].groundType = GetId("GroundTypeCobblestone");

    for (auto x = xStart; x <= xEnd; x++)
        MapArea->tiles[x][yCenter].groundType = GetId("GroundTypeCobblestone");

    for (auto y = yStart; y <= yEnd; y++) {
        if (y == yCenter) continue;

        MapArea->tiles[xStart + 1][y].objects.push_back(
                    MakeSPtr<cObject>("ObjectBush1"));

        MapArea->tiles[xEnd - 1][y].objects.push_back(
                    MakeSPtr<cObject>("ObjectBush1"));

        MapArea->tiles[xStart][y].objects.push_back(
                    MakeSPtr<cObject>("ObjectWoodFence", false, false, 180));

        MapArea->tiles[xEnd][y].objects.push_back(
                    MakeSPtr<cObject>("ObjectWoodFence", false, false, 0));
    }

    for (auto x = xStart; x <= xEnd; x++) {
        if (x == xCenter) continue;

        MapArea->tiles[x][yStart + 1].objects.push_back(
                    MakeSPtr<cObject>("ObjectBush1"));

        MapArea->tiles[x][yEnd - 1].objects.push_back(
                    MakeSPtr<cObject>("ObjectBush1"));

        MapArea->tiles[x][yStart].objects.push_back(
                    MakeSPtr<cObject>("ObjectWoodFence", false, false, 90));

        MapArea->tiles[x][yEnd].objects.push_back(
                    MakeSPtr<cObject>("ObjectWoodFence", false, false, 270));
    }

    auto houseWidth = 4;
    auto houseDepth = 3;

    auto housexCenter = xCenter + 5;
    auto houseyCenter = yCenter + 5;
    auto housexStart = housexCenter - houseWidth/2;
    auto houseyStart = houseyCenter - houseDepth/2;
    auto housexEnd = housexStart + houseWidth;
    auto houseyEnd = houseyStart + houseDepth;

    for (auto y = houseyStart - 1; y <= houseyEnd + 1; y++) {
        for (auto x = housexStart - 1; x <= housexEnd + 1; x++) {
            MapArea->tiles[x][y].elevation = MapArea->tiles[housexCenter][houseyCenter].elevation;
        }
    }

    for (auto y = houseyStart; y <= houseyEnd; y++) {
        for (auto x = housexStart; x <= housexEnd; x++) {
            MapArea->tiles[x][y].roof = MakeSPtr<cObject>("ObjectRoof", false, false);
            MapArea->tiles[x][y].groundType = GetId("GroundTypeWoodfloor");
        }
    }

    for (auto y = houseyStart; y <= houseyEnd; y++) {

        MapArea->tiles[housexStart][y].objects.push_back(
                    MakeSPtr<cObject>("ObjectWoodWall", false, false, 180));

        MapArea->tiles[housexEnd][y].objects.push_back(
                    MakeSPtr<cObject>("ObjectWoodWall", false, false, 0));
    }

    for (auto x = housexStart; x <= housexEnd; x++) {
        if (x != housexCenter)
            MapArea->tiles[x][houseyStart].objects.push_back(
                    MakeSPtr<cObject>("ObjectWoodWall", false, false, 90));



        MapArea->tiles[x][houseyEnd].objects.push_back(
                    MakeSPtr<cObject>("ObjectWoodWall", false, false, 270));
    }

    for (auto y = houseyStart - 1; y != yCenter; y--) {
        MapArea->tiles[housexCenter][y].groundType = GetId("GroundTypeCobblestone");
    }

    auto anvilx = xCenter - 5;
    auto anvily = yCenter - 5;

    for (auto y = anvily - 2; y <= anvily + 2; y++) {
        for (auto x = anvilx - 2; x <= anvilx + 2; x++) {
            MapArea->tiles[x][y].groundType = GetId("GroundTypeCobblestone");
        }
    }

    MapArea->tiles[anvilx][anvily].objects.push_back(
                MakeSPtr<cObject>("ObjectLargeAnvil", false));

    MapArea->tiles[xCenter + 1][yCenter - villageSize/2].objects.push_back(
                MakeSPtr<cObject>("ObjectStreetLantern", false));

    MapArea->tiles[xCenter + 1][yCenter + villageSize/2].objects.push_back(
                MakeSPtr<cObject>("ObjectStreetLantern", false));

    MapArea->tiles[xCenter + villageSize/2][yCenter + 1].objects.push_back(
                MakeSPtr<cObject>("ObjectStreetLantern", false));

    MapArea->tiles[xCenter - villageSize/2][yCenter + 1].objects.push_back(
                MakeSPtr<cObject>("ObjectStreetLantern", false));

}



int
cValleyMapGenerator::DistToPlayerStartingPos(cMapArea *MapArea, int TileX,
                                                  int TileY) const {
  auto DX = MapArea->spawnPos.x - TileX;
  auto DY = MapArea->spawnPos.y - TileY;
  auto Distance = std::sqrt(DX * DX + DY * DY);

  return static_cast<int>(Distance);
}


void
cValleyMapGenerator::GenerateBushes(cMapArea *MapArea) const {
  for (auto I = 0; I < 200; I++) {
    auto TileX = Random.Next() % MapArea->size;
    auto TileY = Random.Next() % MapArea->size;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < PlayerStartingAreaSize)
      continue;

    if (MapArea->tiles[TileX][TileY].groundType == GetId("GroundTypeGrass"))
      if (MapArea->tiles[TileX][TileY].objects.size() == 0)
        MapArea->tiles[TileX][TileY].objects.push_back(
            MakeSPtr<cObject>("ObjectBush1"));
  }
}

void
cValleyMapGenerator::GenerateSmallStones(cMapArea *MapArea) const {
  for (auto I = 0; I < 200; I++) {
    auto TileX = Random.Next() % MapArea->size;
    auto TileY = Random.Next() % MapArea->size;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < PlayerStartingAreaSize)
      continue;

    if (MapArea->tiles[TileX][TileY].groundType != GetId("GroundTypeWater"))
      if (MapArea->tiles[TileX][TileY].objects.size() == 0)
        MapArea->tiles[TileX][TileY].objects.push_back(
            MakeSPtr<cObject>("ObjectSmallStone"));
  }
}

void
cValleyMapGenerator::GeneratePinkFlowers(cMapArea *MapArea) const {
  for (auto I = 0; I < 100; I++) {
    auto TileX = Random.Next() % MapArea->size;
    auto TileY = Random.Next() % MapArea->size;

    if (MapArea->tiles[TileX][TileY].groundType == GetId("GroundTypeGrass"))
      if (MapArea->tiles[TileX][TileY].objects.size() == 0)
        MapArea->tiles[TileX][TileY].objects.push_back(
            MakeSPtr<cObject>("ObjectPinkFlower"));
  }
}

void
cValleyMapGenerator::GenerateTallGrass(cMapArea *MapArea) const {
  for (auto I = 0; I < 6000; I++) {
    auto TileX = Random.Next() % MapArea->size;
    auto TileY = Random.Next() % MapArea->size;

    if (MapArea->tiles[TileX][TileY].groundType == GetId("GroundTypeGrass"))
      if (MapArea->tiles[TileX][TileY].objects.size() == 0)
        MapArea->tiles[TileX][TileY].objects.push_back(
            MakeSPtr<cObject>("ObjectTallGrass"));
  }
}


void
cValleyMapGenerator::GenerateMobs(cMapArea *MapArea) const {
  for (auto I = 0; I < 100; I++) {
    auto TileX = Random.Next() % MapArea->size;
    auto TileY = Random.Next() % MapArea->size;

    if (TileX == static_cast<int>(MapArea->spawnPos.x)
            && TileY == static_cast<int>(MapArea->spawnPos.y))
        continue;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < PlayerStartingAreaSize)
      continue;

    if (MapArea->tiles[TileX][TileY].groundType !=
            GetId("GroundTypeWater") &&
        MapArea->tiles[TileX][TileY].actor == nullptr) {
      MapArea->tiles[TileX][TileY].actor =
          std::make_unique<cMob>(Engine,
                                 static_cast<float>(TileX),
                                 static_cast<float>(TileY),
                                 "MobRabbit");
      MapArea->mobActorsMirror.push_back(
                  std::ref(MapArea->tiles[TileX][TileY].actor));
    }
  }

  for (auto I = 0; I < 100; I++) {
    auto TileX = Random.Next() % MapArea->size;
    auto TileY = Random.Next() % MapArea->size;

    if (TileX == static_cast<int>(MapArea->spawnPos.x)
            && TileY == static_cast<int>(MapArea->spawnPos.y))
        continue;

    if (DistToPlayerStartingPos(MapArea, TileX, TileY) < PlayerStartingAreaSize)
      continue;

    if (MapArea->tiles[TileX][TileY].groundType !=
            GetId("GroundTypeWater") &&
        MapArea->tiles[TileX][TileY].actor == nullptr) {
      MapArea->tiles[TileX][TileY].actor =
          std::make_unique<cMob>(Engine,
                                 static_cast<float>(TileX),
                                 static_cast<float>(TileY),
                                 "MobRat");
      MapArea->mobActorsMirror.push_back(
                  std::ref(MapArea->tiles[TileX][TileY].actor));
    }
  }
}


}  // namespace Forradia
