// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cWorldMap.h"
#include "CommonExternal.h"
#include "framework/iMapGenerator.h"

namespace Forradia {

void cWorldMap::GenerateWorldMap(iMapGenerator &MapGenerator) {

  for (auto WorldY = 0; WorldY < 3; WorldY++)
    for (auto WorldX = 0; WorldX < 3; WorldX++)

      MapGenerator.GenerateMapArea(WorldX, WorldY, 0);
}

}  // namespace Forradia
