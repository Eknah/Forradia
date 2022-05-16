// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "Point2F.h"
#include "IModule.h"

namespace Forradia
{

    class DestMovmModule : public IModule
    {

        // Functions

    public:

        DestMovmModule(const IEngine& _e, Actor* _parentActor);

        void ResetForNewFrame() override {};
        void Update() override;

    };

}  // namespace Forradia
