#pragma once
#include "../core/Aliases.h"
#include "CMob.h"
#include "CObject.h"

namespace Forradia
{

class CEngine;

class CTile
{

public:

    CTile(CEngine& engine) : Engine(engine) {}

    // Get info about tile
    bool MovementBlocked();
    bool HasObjectOfType(std::string objectName);

    // Core tile data structure
    int GroundType = 0;
    std::vector<UPtr<CObject>> Objects;
    int Elevation = 0;
    UPtr<CMob> mob = nullptr;
    int WarpToMap = -1;

private:
    CEngine& Engine;

};

}
