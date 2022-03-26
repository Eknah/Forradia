
#include "CommonExternal.h"
#include "F_WorldMap.h"
#include "framework/F_IMapGenerator.h"

namespace Forradia
{

void F_WorldMap::GenerateWorldMap(F_IMapGenerator& mapGenerator)
{

    for (auto worldy = 0; worldy < 3; worldy++)
        for (auto worldx = 0; worldx < 3; worldx++)
            mapGenerator.GenerateMapArea({worldx, worldy});

}

}
