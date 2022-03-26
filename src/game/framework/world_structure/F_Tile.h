#pragma once
#include "../core/Aliases.h"
#include "F_Mob.h"
#include "F_Object.h"

namespace Forradia
{

class F_Engine;

class F_Tile
{

public:

    F_Tile(F_Engine& engine) : Engine(engine) {}

    // Get info about tile
    bool MovementBlocked();
    bool HasObjectOfType(std::string objectName);

    // Core tile data structure
    int GroundType = 0;
    std::vector<UPtr<F_Object>> Objects;
    int Elevation = 0;
    UPtr<F_Mob> mob = nullptr;
    int WarpToMap = -1;

private:
    F_Engine& Engine;

};

}
