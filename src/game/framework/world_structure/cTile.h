
#pragma once
#include "../engine/Aliases.h"
#include "cMob.h"
#include "cObject.h"

namespace Forradia
{

class cEngine;

class cTile
{

public:

    cTile(cEngine& Engine_) : Engine(Engine_) {}

    // Get info about tile
    bool MovementBlocked();
    bool HasObjectOfType(std::string ObjectName);

    // Core tile data structure
    int                         GroundType = 0;
    std::vector<UPtr<cObject>>  Objects;
    int                         Elevation = 0;
    UPtr<cMob>                  Mob = nullptr;
    int                         WarpToFloor = -1;

private:
    cEngine& Engine;

};

}
