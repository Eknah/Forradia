#include "CommonExternal.h"
#include "F_PlanetTransformator.h"
#include "../core/F_Engine.h"

namespace Forradia
{

float F_PlanetTransformator::GetNewY(float tiley, float mapx, float mapy)
{
    auto result = tiley;
    auto dx = (int)mapx - Engine.Player.Position.X;
    auto dy = (int)mapy - Engine.Player.Position.Y;
    auto distance = dx * dx + dy * dy;

    result -= distance*0.01f;

    return result;
}

}
