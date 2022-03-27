
#pragma once
#include "CommonExternal.h"
#include "../core/Aliases.h"
#include "modules/F_IModule.h"
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
    inline T& GetModule()
    {
        return static_cast<T&>(*Modules.at(typeid(T).hash_code()));
    }

    int CurrentMapArea = 0;
    F_Point2F Position = { 50.0f, 50.0f };

protected:

    template <class T>
    inline void AddModule()
    {
        auto& Type = typeid(T);
        Modules.insert({Type.hash_code(),MakeUPtr<T>(Engine, *this)});
    }

private:

    F_IEngine& Engine;
    UMap<size_t, UPtr<F_IModule>> Modules;


};

}
