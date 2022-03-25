#pragma once
namespace Forradia
{

class CMapArea
{

public:

    CMapArea(CEngine& Engine, int mapAreaSize);

    // Basic data
    int Size = -1;
    bool IsCave = False;
    CPoint2F PlayerStartPosition = {-1, -1};

    // Map structure of tiles and mobs
    List<List<CTile>> Tiles;
    List<std::reference_wrapper<UPtr<CMob>>> MobsMirror;

};

}
