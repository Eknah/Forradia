
#pragma once
#include "F_IModule.h"
#include "../core/Aliases.h"
#include "framework/world_structure/F_Object.h"

namespace Forradia
{

class F_ModuleInventory : public F_IModule
{

public:

    using F_IModule::F_IModule;

    void ResetForNewFrame() override;
    void Update() override;

    // Collection operations
    void Add(int Position, std::string ObjectName);

    // Collection structure
    UMap<int, SPtr<F_Object>> Objects;

};

}
