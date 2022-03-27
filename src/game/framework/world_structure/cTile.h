
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

    cTile(cEngine& engine) : Engine(engine) {}

    // Get info about tile
    bool MovementBlocked();
    bool HasObjectOfType(std::string objectName);

    // Core tile data structure
    int GroundType = 0;
    std::vector<UPtr<cObject>> Objects;
    int Elevation = 0;
    UPtr<cMob> mob = nullptr;
    int WarpToFloor = -1;

private:
    cEngine& Engine;

};

}
