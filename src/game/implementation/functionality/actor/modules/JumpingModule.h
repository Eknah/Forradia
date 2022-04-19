// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "../engine/IModule.h"
#include "../engine/Timer.h"
#include "../engine/Aliases.h"

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
        float maxJumpHeight = 1.0f;

        int jumpDuration = 600;
        Timer timer = Timer(UPtr<int>(&jumpDuration));

    };

}  // namespace Forradia
