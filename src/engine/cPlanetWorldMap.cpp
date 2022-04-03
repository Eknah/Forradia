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

cRect cPlanetWorldMap::GetBounds() {
    auto minx = std::numeric_limits<int>::max();
    auto miny = std::numeric_limits<int>::max();
    auto maxx = std::numeric_limits<int>::min();
    auto maxy = std::numeric_limits<int>::min();

    for (auto &[x, entry] : areas) {
        if (x < minx)
            minx = x;
        if (x > maxx)
            maxx = x;

        for (auto &[y, area] : entry) {
            if (y < miny)
                miny = y;
            if (y > maxy)
                maxy = y;

        }

    }
    return {minx, miny, maxx - minx, maxy - miny};
}

UPtr<cMapArea>& cPlanetWorldMap::GetArea(cPoint3 Pos) {
    return areas[Pos.x][Pos.y][Pos.z];
}

}  // namespace Forradia
