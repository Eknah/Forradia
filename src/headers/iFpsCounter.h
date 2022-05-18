// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "Palette.h"

namespace Forradia
{
    class IEngine;

    class IFpsCounter
    {
    public:
        explicit IFpsCounter(IEngine& _e)
		: e(_e) {}

        virtual void Update() = 0;
        virtual void Render() = 0;

    protected:
        IEngine& e;
        int framesCount = 0;
        int fps = 0;
        const float w = 0.07f;
        const float h = 0.03f;
        const float posx = 0.97f;
        const float posy = 1.0f - h / 2;
    };
}