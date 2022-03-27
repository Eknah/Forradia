
#pragma once
#include "framework/actor/cActor.h"
#include "framework/actor/modules/cModuleJumping.h"
#include "framework/actor/modules/cModuleMovement.h"
#include "framework/actor/modules/cModuleInventory.h"
#include "framework/actor/modules/cModuleObjectUsage.h"

namespace Forradia
{


class cPlayer : public cActor
{

public:

    cPlayer(iEngine& engine) : cActor(engine)
    {
        AddModule<cModuleJumping>();
        AddModule<cModuleMovement>();
        AddModule<cModuleInventory>();
        AddModule<cModuleObjectUsage>();
    }

};

}
