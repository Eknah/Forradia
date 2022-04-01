// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cWorldMap.h"
#include "../engine/iMapGenerator.h"

namespace Forradia {

void cWorldMap::GenerateWorldMap(UMap<int, UMap<int, SPtr<iMapGenerator>>> GenAreas) {
    for (auto& [X, Remain] : GenAreas) {
        for (auto& [Y, Gen] : Remain) {
            Gen->GenerateMapArea(X, Y, 0);
        }
    }
}

UPtr<cMapArea>& cWorldMap::GetArea(cPoint3 Pos) {
    return Areas[Pos.X][Pos.Y][Pos.Z];
}

}  // namespace Forradia
