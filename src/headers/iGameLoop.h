// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia
{
    class IEngine;

    class IGameLoop
    {
    public:
        explicit IGameLoop(IEngine& _e) : e(_e) {}

        virtual void Run() = 0;

        // Looped functions
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void ResetForNewFrame() = 0;

        bool quit = false;
        int lowResWidth = 400;
        int lowResHeight = 300;

    protected:
        IEngine& e;
    };
}