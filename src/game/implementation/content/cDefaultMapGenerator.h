// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cMapArea.h"
#include "framework/iMapGenerator.h"

namespace Forradia {

class cDefaultMapGenerator : public iMapGenerator {
 public:
  using iMapGenerator::iMapGenerator;

  void GenerateMapArea(int WorldX, int WorldY, int WorldZ) override;

 private:
  void ClearToGrass(cMapArea &MapArea);
  void GeneratePlayerStartingPosition(cMapArea &MapArea);
  void GenerateElevation(cMapArea &MapArea);
  void GenerateWater(cMapArea &MapArea);
  void GenerateSand(cMapArea &MapArea);
  void GenerateClay(cMapArea &MapArea);
  void GenerateRock(cMapArea &MapArea);
  void GenerateTrees(cMapArea &MapArea);
  void GenerateBushes(cMapArea &MapArea);
  void GenerateSmallStones(cMapArea &MapArea);
  void GeneratePinkFlowers(cMapArea &MapArea);
  void GenerateMobs(cMapArea &MapArea);
  void GenerateQuestCaves(cEngine &Engine, cMapArea &MapArea,
                          UPtr<cWorldMap> &WorldMap);
  int DistToPlayerStartingPos(cMapArea &MapArea, int TileX, int TileY);

  const int PlayerStartingAreaSize = 4;
};

} // namespace Forradia
