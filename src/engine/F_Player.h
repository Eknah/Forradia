
#pragma once
#include "framework/actor/F_Actor.h"
#include "framework/actor/modules/F_ModuleJumping.h"
#include "framework/actor/modules/F_ModuleMovement.h"
#include "framework/actor/modules/F_ModuleInventory.h"
#include "framework/actor/modules/F_ModuleObjectUsage.h"

namespace Forradia
{


class F_Player : public F_Actor
{

public:

    F_Player(F_IEngine& engine) : F_Actor(engine)
    {
        AddModule<F_ModuleJumping>();
        AddModule<F_ModuleMovement>();
        AddModule<F_ModuleInventory>();
        AddModule<F_ModuleObjectUsage>();
    }

};

}
