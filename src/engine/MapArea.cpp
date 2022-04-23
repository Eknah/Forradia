// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "MapArea.h"
#include "../engine/Tile.h"

namespace Forradia
{

    MapArea::MapArea(const IEngine& e, int _size, Point3 worldPos) : size(_size), worldCoord(worldPos)
    {
        for (auto x = 0; x < size; x++)
        {
            tiles.push_back(std::vector<Tile>());

            for (auto y = 0; y < size; y++)
                tiles[x].push_back(Tile(e));
        }
    }

    Actor& MapArea::AddActor(UPtr<Actor> Actor, int TileX, int TileY)
    {
        tiles[TileX][TileY].actor = std::move(Actor);
        return *tiles[TileX][TileY].actor;
    }

    bool MapArea::IsUnderground()
    {
        return worldCoord.z < 0;
    }

    Tile& MapArea::GetTile(Point2 Pos)
    {
        return tiles[Pos.x][Pos.y];
    }

    std::vector<std::reference_wrapper<Tile>> MapArea::AllTiles()
    {
        std::vector<std::reference_wrapper<Tile>> result;

        for (auto y = 0; y < size; y++)
        {
            for (auto x = 0; x < size; x++)
            {
                result.push_back(std::ref(tiles[x][y]));
            }
        }

        return result;
    }

    Point2F MapArea::RandCoordF()
    {
        return { CFloat(rnd.Next(size)), CFloat(rnd.Next(size)) };
    }

    Point2 MapArea::RandCoordI()
    {
        return { rnd.Next(size), rnd.Next(size)};
    }
    bool MapArea::Contains(Point2 p, int margin)
    {
        return p.x >= margin && p.y >= margin && p.x < size - margin && p.y < size - margin;
    }

}  // namespace Forradia
