
#include "CommonExternal.h"
#include "F_MapArea.h"

namespace Forradia
{

F_MapArea::F_MapArea(F_Engine& Engine, int mapAreaSize) : Size(mapAreaSize)
{
    for (auto x = 0; x < Size; x++)
    {
        Tiles.push_back(std::vector<F_Tile>());

        for (auto y = 0; y < Size; y++)
            Tiles[x].push_back(F_Tile(Engine));
    }
}

}
