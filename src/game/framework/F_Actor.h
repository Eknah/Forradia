
#pragma once
#include "../core/Aliases.h"
#include "actor_modules/F_IActorModule.h"
#include "../core/F_Point2F.h"

namespace Forradia
{

class F_Actor
{
public:

    void ResetForNewFrame();
    void Update();
    F_IActorModule& GetModule(std::string ModuleName);

    int CurrentMapArea = 0;
    F_Point2F Position = { 50.0f, 50.0f };

protected:

    void AddModule(std::string ModuleName, F_IActorModule& Module);

    UMap<int, F_IActorModule&> Modules;

};

}
