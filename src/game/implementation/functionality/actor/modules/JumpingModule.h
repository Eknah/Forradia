// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/IModule.h"

namespace Forradia
{

    class JumpingModule : public IModule
    {
    public:
        using IModule::IModule;

        void ResetForNewFrame() override;
        void Update() override;
        void Jump();


    private:
        bool isJumping = false;
        int jumpDuration = 600;
        unsigned int tickStartJumping = 0;
        float maxJumpHeight = 1.0f;
    };

}  // namespace Forradia
