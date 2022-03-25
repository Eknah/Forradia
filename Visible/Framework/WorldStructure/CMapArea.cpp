#include "CommonExternal.h"
#include "CMapArea.h"
namespace Forradia
{
CMapArea::CMapArea(CEngine& Engine, int mapAreaSize) : Size(mapAreaSize)
{
    for (auto x = 0; x < Size; x++)
    {
        Tiles.push_back(std::vector<CTile>());
        for (auto y = 0; y < Size; y++)
            Tiles[x].push_back(CTile(Engine));
    }
}
}
