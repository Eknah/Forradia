// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "Aliases.h"
#include "IModule.h"
#include "Inventory.h"

namespace Forradia
{

    class InventoryModule : public IModule
    {

    public:

        using IModule::IModule;

        void ResetForNewFrame() override;
        void Update() override;
        void Add(int position, std::string objectName);

        Inventory inventory;

    };

}