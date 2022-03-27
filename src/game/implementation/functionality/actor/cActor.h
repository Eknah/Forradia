
#pragma once
#include "CommonExternal.h"
#include "../engine/Aliases.h"
#include "modules/iModule.h"
#include "../engine/cPoint2F.h"

namespace Forradia
{

class iEngine;

class cActor
{
public:

    cActor(iEngine& Engine_) : Engine(Engine_) {}

    void ResetForNewFrame();
    void Update();

    template <class T>
    inline T& GetModule()
    {
        return static_cast<T&>(*Modules.at(typeid(T).hash_code()));
    }

    int CurrentMapArea = 0;
    cPoint2F Position = { 50.0f, 50.0f };

protected:

    template <class T>
    inline void AddModule()
    {
        auto& Type = typeid(T);
        Modules.insert({Type.hash_code(),MakeUPtr<T>(Engine, *this)});
    }

private:

    iEngine& Engine;
    UMap<size_t, UPtr<iModule>> Modules;


};

}
