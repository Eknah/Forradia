// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "../engine/Point2F.h"
#include "../engine/IModule.h"

namespace Forradia
{

    class DestMovmModule : public IModule
    {

    public:

        DestMovmModule(const IEngine& _e, Actor* _parentActor);

        void ResetForNewFrame() override {};
        void Update() override;

    };

}  // namespace Forradia
