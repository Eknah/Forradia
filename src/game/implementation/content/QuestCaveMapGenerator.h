// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Random.h"
#include "../engine/MapArea.h"
#include "../engine/Point2.h"

namespace Forradia {

class cQuestCaveMapGenerator {
 public:
  void GenerateQuestCaveMapArea(cMapArea *mapArea, cPoint2 entranceLocation);

 private:
  void ClearToCaveFloor(cMapArea *mapArea);
  void GenerateCaveWalls(cMapArea *mapArea);
  void GeneratePath(cMapArea *mapArea, cPoint2 entranceLocation);

  cRandom random;
};

}  // namespace Forradia
