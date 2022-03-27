
#pragma once
#include "F_IModule.h"
#include "framework/world_structure/F_Object.h"

namespace Forradia
{

class F_ModuleObjectUsage : public F_IModule
{

public:

    using F_IModule::F_IModule;

    void ResetForNewFrame() override;
    void Update() override;

    SPtr<F_Object> ObjectBeingUsed = nullptr;

};

}
