
#pragma once

namespace Forradia
{

class F_ObjectDescription
{

public:

    F_ObjectDescription() = default;
    F_ObjectDescription(bool movable, bool blocksMovement, bool blocksSight) : Movable(movable), BlocksMovement(blocksMovement), BlocksSight(blocksSight) {}

    // Description parameters
    bool Movable = false;
    bool BlocksMovement = false;
    bool BlocksSight = false;

};

}
