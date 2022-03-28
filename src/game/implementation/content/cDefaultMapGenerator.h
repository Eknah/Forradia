// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cRandom.h"
#include "../engine/cMapArea.h"
#include "framework/iMapGenerator.h"

namespace Forradia {

class cDefaultMapGenerator : public iMapGenerator {
 public:
  using iMapGenerator::iMapGenerator;

  void GenerateMapArea(int WorldX, int WorldY, int WorldZ) const override;

 private:
  void ClearToGrass(cMapArea *MapArea) const;
  void GeneratePlayerStartingPosition(cMapArea *MapArea) const;
  void GenerateElevation(cMapArea *MapArea) const;
  void GenerateWater(cMapArea *MapArea) const;
  void GenerateSand(cMapArea *MapArea) const;
  void GenerateClay(cMapArea *MapArea) const;
  void GenerateRock(cMapArea *MapArea) const;
  void GenerateTrees(cMapArea *MapArea) const;
  void GenerateBushes(cMapArea *MapArea) const;
  void GenerateSmallStones(cMapArea *MapArea) const;
  void GeneratePinkFlowers(cMapArea *MapArea) const;
  void GenerateMobs(cMapArea *MapArea) const;
  void GenerateQuestCaves(const cEngine &Engine, cMapArea *MapArea,
                          const UPtr<cWorldMap> &WorldMap) const;
  int DistToPlayerStartingPos(cMapArea *MapArea, int TileX, int TileY) const;

  const int PlayerStartingAreaSize = 4;
  cRandom Random;
};

}  // namespace Forradia
