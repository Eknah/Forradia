
#include "CommonExternal.h"
#include "cWorldMap.h"
#include "framework/iMapGenerator.h"

namespace Forradia
{

void cWorldMap::GenerateWorldMap(iMapGenerator& MapGenerator)
{

    for (auto WorldY = 0; WorldY < 3; WorldY++)
        for (auto WorldX = 0; WorldX < 3; WorldX++)

            MapGenerator.GenerateMapArea(WorldX, WorldY, 0);

}

}
