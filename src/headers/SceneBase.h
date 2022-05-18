// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "SDL2/SDL.h"
#include "TextRect.h"
#include <vector>
#include "Aliases.h"

namespace Forradia
{

    class Engine;

    class SceneBase
    {

        // Functions

    public:

        explicit SceneBase(Engine& _e) : e(_e) {}

        virtual void Enter() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void MouseDown(Uint8 button) = 0;
        virtual void MouseUp(Uint8 button) = 0;
        virtual void KeyDown(SDL_Keycode key) = 0;
        virtual void KeyUp(SDL_Keycode key) = 0;

        // Members

    protected:

        Engine& e;

        List<TextRect> sceneButtons;
    };

}  // namespace Forradia
