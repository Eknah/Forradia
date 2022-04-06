// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cRandom.h"
#include "../engine/cMapArea.h"
#include "../engine/iMapGenerator.h"

namespace Forradia {

class cValleyMapGenerator : public iMapGenerator {
 public:
  using iMapGenerator::iMapGenerator;

  void GenerateMapArea(int worldX, int worldY, int worldZ) const override;

 private:
  void ClearToGrass(cMapArea *mapArea) const;
  void GeneratePlayerStartingPosition(cMapArea *mapArea) const;
  void GenerateElevation(cMapArea *mapArea) const;
  void GenerateRock(cMapArea *mapArea) const;
  void GenerateVillage(cMapArea *mapArea) const;
  void GenerateTrees(cMapArea *mapArea) const;
  void GenerateBushes(cMapArea *mapArea) const;
  void GenerateSmallStones(cMapArea *mapArea) const;
  void GeneratePinkFlowers(cMapArea *mapArea) const;
  void GenerateTallGrass(cMapArea *mapArea) const;
  void GenerateMobs(cMapArea *mapArea) const;

  int DistToPlayerStartingPos(cMapArea *mapArea, int tileX, int tileY) const;

  const int playerStartingAreaSize = 4;
  cRandom random;
  int villageSize = 17;
};

}  // namespace Forradia
