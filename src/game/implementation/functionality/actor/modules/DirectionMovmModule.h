// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "../engine/Point2F.h"
#include "../engine/IModule.h"
#include "../engine/MoveDir.h"

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

}  // namespace Forradia
