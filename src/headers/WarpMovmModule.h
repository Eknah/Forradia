// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "IModule.h"

namespace Forradia
{

    class WarpMovmModule : public IModule
    {

        // Functions

    public:
        using IModule::IModule;

        void ResetForNewFrame() override {};
        void Update() override {};
        void WarpIfStandOnPortal();

    };

}  // namespace Forradia
