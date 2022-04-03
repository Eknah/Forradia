// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cPlanetWorldMap.h"
#include "../engine/iMapGenerator.h"

namespace Forradia {

void cPlanetWorldMap::GenerateWorldMap(UMap<int, UMap<int, SPtr<iMapGenerator>>> GenAreas) {
    for (auto& [X, Remain] : GenAreas) {
        for (auto& [Y, Gen] : Remain) {
            Gen->GenerateMapArea(X, Y, 0);
        }
    }
}

UPtr<cMapArea>& cPlanetWorldMap::GetArea(cPoint3 Pos) {
    return areas[Pos.x][Pos.y][Pos.z];
}

}  // namespace Forradia
