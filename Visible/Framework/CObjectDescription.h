#pragma once
namespace Forradia
{

class CObjectDescription
{

public:

    CObjectDescription() = default;
    CObjectDescription(bool movable, bool blocksMovement, bool blocksSight) : Movable(movable), BlocksMovement(blocksMovement), BlocksSight(blocksSight) {}

    // Description parameters
    bool Movable = False;
    bool BlocksMovement = False;
    bool BlocksSight = False;

};

}
