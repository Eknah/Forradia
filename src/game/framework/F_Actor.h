
#pragma once
#include "../core/Aliases.h"
#include "actor_modules/F_IActorModule.h"
#include "../core/F_Point2F.h"

namespace Forradia
{

class F_IEngine;

class F_Actor
{
public:

    F_Actor(F_IEngine& Engine_) : Engine(Engine_) {}

    void ResetForNewFrame();
    void Update();

    template <class T>
    inline T& GetModule(std::string ModuleName)
    {
        return static_cast<T&>(Modules.at(GetId(ModuleName)));
    }

    int CurrentMapArea = 0;
    F_Point2F Position = { 50.0f, 50.0f };

protected:

    template <class T>
    inline void AddModule(std::string ModuleName)
    {
        ModulesPtrs.insert({GetId(ModuleName), MakeUPtr<T>(Engine, *this)});
        Modules.insert({GetId(ModuleName),*ModulesPtrs.at(GetId(ModuleName))});
    }

    UMap<int, F_IActorModule&> Modules;

private:

    F_IEngine& Engine;
    UMap<int, UPtr<F_IActorModule>> ModulesPtrs;

};

}
