
#pragma once
#include "../engine/iModule.h"
#include "../engine/Aliases.h"
#include "framework/world_structure/cObject.h"

namespace Forradia
{

class cModuleInventory : public iModule
{

public:

    using   iModule::iModule;

    void    ResetForNewFrame() override;
    void    Update() override;

    // Collection operations

    void    Add(int Position, std::string ObjectName);

    // Collection structure

    UMap<int, SPtr<cObject>>
    Objects;

};

}
