// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "IModule.h"
#include "Timer.h"
#include "Aliases.h"

namespace Forradia
{
    class JumpingModule : public IModule
    {
        // Functions
    public:
        using IModule::IModule;

        void ResetForNewFrame() override;
        void Update() override;
        void Jump();

        // Members
    private:
        bool isJumping = false;
        float maxJumpHeight = 1.0f;
        int jumpDuration = 600;
        Timer timer = Timer(UPtr<int>(&jumpDuration));
    };
}