// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cMapArea.h"
#include "../engine/cPoint2.h"

namespace Forradia {

class cQuestCaveMapGenerator {
 public:
  void GenerateQuestCaveMapArea(cMapArea &MapArea, cPoint2 EntranceLocation);

 private:
  void ClearToCaveFloor(cMapArea &MapArea);
  void GenerateCaveWalls(cMapArea &MapArea);
  void GeneratePath(cMapArea &MapArea, cPoint2 EntranceLocation);
};

}  // namespace Forradia
