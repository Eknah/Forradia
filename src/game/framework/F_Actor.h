
#pragma once
#include "../core/Aliases.h"
#include "actor_modules/F_IActorModule.h"

namespace Forradia
{

class F_Actor
{
public:

    void Update();
    F_IActorModule& GetModule(std::string ModuleName);

protected:

    void AddModule(std::string ModuleName, F_IActorModule& Module);

    UMap<int, F_IActorModule&> Modules;

};

}
