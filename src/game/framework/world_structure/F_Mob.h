#pragma once
#include "../core/F_Point2F.h"

namespace Forradia
{

class F_Mob
{

public:

    F_Mob(float x, float y) : Position(x, y) {}

    // Movement
    int TickLastMove = 0;
    int MoveSpeed = 30;
    float StepSize = 1.0f;
    float StepMultiplier = 0.1f;
    F_Point2F MoveDestination = {-1, -1};

    // Rotation
    float FacingAngle = 0.0f;

    // Localization
    F_Point2F Position = {-1, -1};
};

}
