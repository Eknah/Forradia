#include "CommonExternal.h"
#include "CWorldMap.h"
#include "Framework/IMapGenerator.h"

namespace Forradia
{

void CWorldMap::GenerateWorldMap(IMapGenerator& mapGenerator)
{

    for (auto worldy = 0; worldy < 3; worldy++)
        for (auto worldx = 0; worldx < 3; worldx++)
            mapGenerator.GenerateMapArea({worldx, worldy});

}

}
