// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Random.h"
#include "../engine/MapArea.h"
#include "../engine/IMapGenerator.h"

namespace Forradia {

class DefaultMapGenerator : public IMapGenerator {
 public:
  using IMapGenerator::IMapGenerator;

  void GenerateMapArea(int worldX, int worldY, int worldZ) const override;

 private:
  void ClearToGrass(MapArea *mapArea) const;
  void GeneratePlayerStartingPosition(MapArea *mapArea) const;
  void GenerateElevation(MapArea *mapArea) const;
  void GenerateWater(MapArea *mapArea) const;
  void GenerateSand(MapArea *mapArea) const;
  void GenerateClay(MapArea *mapArea) const;
  void GenerateRock(MapArea *mapArea) const;
  void GenerateTrees(MapArea *mapArea) const;
  void GenerateBushes(MapArea *mapArea) const;
  void GenerateSmallStones(MapArea *mapArea) const;
  void GeneratePinkFlowers(MapArea *mapArea) const;
  void GenerateTallGrass(MapArea *mapArea) const;
  void GenerateMobs(MapArea *mapArea) const;
  void GenerateQuestCaves(const IEngine &e, MapArea *mapArea,
                          const UPtr<PlanetWorldMap> &worldMap) const;
  int DistToPlayerStartingPos(MapArea *mapArea, int tileX, int tileY) const;

  const int playerStartingAreaSize = 4;
  Random random;
};

}  // namespace Forradia