// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "Point2F.h"
#include "IModule.h"
#include "MoveDir.h"

namespace Forradia
{

    class DirectionMovmModule : public IModule
    {

        // Funcitons

    public:

        DirectionMovmModule(const IEngine& _e, Actor* _parentActor);

        void ResetForNewFrame() override {};
        void Update() override;

        // Members

    public:
        char moveInstruction;

    };

}