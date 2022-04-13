// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "SDL2/SDL.h"
#include "TextRect.h"
#include <vector>
#include "../engine/Aliases.h"

namespace Forradia
{

    class Engine;

    class SceneBase
    {
    public:

        explicit SceneBase(const Engine& _e) : e(_e) {}

        virtual void Enter() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void DoMouseDown(Uint8 button) = 0;
        virtual void DoMouseUp(Uint8 button) = 0;

    protected:

        const Engine& e;

        List<TextRect> sceneButtons;
    };

}  // namespace Forradia
