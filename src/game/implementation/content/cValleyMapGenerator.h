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

  void GenerateMapArea(int WorldX, int WorldY, int WorldZ) const override;

 private:
  void ClearToGrass(cMapArea *MapArea) const;
  void GeneratePlayerStartingPosition(cMapArea *MapArea) const;
  void GenerateElevation(cMapArea *MapArea) const;
  void GenerateRock(cMapArea *MapArea) const;
  void GenerateVillage(cMapArea *MapArea) const;
  void GenerateTrees(cMapArea *MapArea) const;
  void GenerateBushes(cMapArea *MapArea) const;
  void GenerateSmallStones(cMapArea *MapArea) const;
  void GeneratePinkFlowers(cMapArea *MapArea) const;
  void GenerateTallGrass(cMapArea *MapArea) const;
  void GenerateMobs(cMapArea *MapArea) const;

  int DistToPlayerStartingPos(cMapArea *MapArea, int TileX, int TileY) const;

  const int PlayerStartingAreaSize = 4;
  cRandom Random;
  int villageSize = 17;
};

}  // namespace Forradia
