// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cWorldMap.h"
#include "CommonExternal.h"
#include "framework/iMapGenerator.h"

namespace Forradia {

void cWorldMap::GenerateWorldMap(const iMapGenerator &MapGenerator) {
//  for (auto WorldY = 0; WorldY < 3; WorldY++)
//    for (auto WorldX = 0; WorldX < 3; WorldX++)

//        for (auto WorldY = 0; WorldY < 1; WorldY++)
//          for (auto WorldX = 0; WorldX < 1; WorldX++)
            for (auto WorldY = 0; WorldY < WorldMapHeight; WorldY++)
              for (auto WorldX = 0; WorldX < WorldMapWidth; WorldX++)
      MapGenerator.GenerateMapArea(WorldX, WorldY, 0);
}

UPtr<cMapArea>& cWorldMap::GetArea(cPoint3 Pos) {
    return Areas[Pos.X][Pos.Y][Pos.Z];
}

}  // namespace Forradia
