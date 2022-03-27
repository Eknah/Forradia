
#include "CommonExternal.h"
#include "F_Player.h"
#include "../core/F_Engine.h"

namespace Forradia
{


void F_Player::UpdateRotation(float newFacingAngle)
{
    GetModule<F_ActorModuleMovement>("ModuleMovement").FacingAngle = newFacingAngle;
}

}
