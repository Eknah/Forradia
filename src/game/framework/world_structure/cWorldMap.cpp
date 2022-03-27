
#include "CommonExternal.h"
#include "cWorldMap.h"
#include "framework/iMapGenerator.h"

namespace Forradia
{

void cWorldMap::GenerateWorldMap(iMapGenerator& mapGenerator)
{

    for (auto worldy = 0; worldy < 3; worldy++)
        for (auto worldx = 0; worldx < 3; worldx++)
            mapGenerator.GenerateMapArea({worldx, worldy});

}

}
