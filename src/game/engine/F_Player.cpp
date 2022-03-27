
#include "CommonExternal.h"
#include "F_Player.h"
#include "../core/F_Engine.h"

namespace Forradia
{


void F_Player::UpdateRotation(float newFacingAngle)
{
    ModuleMovement.FacingAngle = newFacingAngle;
}

}
