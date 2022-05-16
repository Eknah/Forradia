// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "Utilities.h"
#include "Palette.h"
#include "SceneBase.h"

namespace Forradia
{

    class SceneMainMenu : public SceneBase
    {

    public:

        using SceneBase::SceneBase;

        void Enter() override;
        void Update() override {};
        void Render() override;
        void MouseDown(Uint8 mouseButton) override;
        void MouseUp(Uint8 mouseButton) override {}
        void KeyDown(SDL_Keycode key) override;
        void KeyUp(SDL_Keycode key) override {}

    private:

        Utilities utils;

    };

}  // namespace Forradia
