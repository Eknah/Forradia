
#pragma once
#include "implementation/functionality/actor/cActor.h"
#include "implementation/functionality/actor/modules/cModuleJumping.h"
#include "implementation/functionality/actor/modules/cModuleMovement.h"
#include "implementation/functionality/actor/modules/cModuleInventory.h"
#include "implementation/functionality/actor/modules/cModuleObjectUsage.h"

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
