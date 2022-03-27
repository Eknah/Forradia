
#include "CommonExternal.h"
#include "cMapArea.h"

namespace Forradia
{

cMapArea::cMapArea(cEngine& Engine, int mapAreaSize, int WorldX, int WorldY, int WorldZ) : Size(mapAreaSize), WorldCoord({WorldX, WorldY, WorldZ})
{
    for (auto x = 0; x < Size; x++)
    {
        Tiles.push_back(std::vector<cTile>());

        for (auto y = 0; y < Size; y++)
            Tiles[x].push_back(cTile(Engine));
    }
}

bool cMapArea::IsUnderground()
{
    return WorldCoord.Z < 0;
}

}
