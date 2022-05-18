// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia
{

    class IEngine;

    class IFullscreenController
    {
    public:
        explicit IFullscreenController(const IEngine& _e) : e(_e) {}

        virtual void UpdateFullscreenToggling() = 0;
        virtual void ToggleFullscreen() = 0;

    protected:
        const IEngine& e;
        bool fullscreenOn = true;
    };

}