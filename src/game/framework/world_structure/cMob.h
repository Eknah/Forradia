
#pragma once

#include "../engine/cPoint2F.h"

namespace Forradia
{

class cMob
{

public:

    cMob(float X, float Y) : Position(X, Y) {}

    // Movement

    unsigned int    TickLastMove = 0;
    int             MoveSpeed = 30;
    float           StepSize = 1.0f;
    float           StepMultiplier = 0.1f;
    cPoint2F        MoveDestination = {-1, -1};

    // Rotation

    float           FacingAngle = 0.0f;

    // Localization

    cPoint2F        Position = {-1, -1};
};

}
