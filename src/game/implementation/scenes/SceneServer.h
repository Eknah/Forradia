// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Utilities.h"
#include "../engine/Palette.h"
#include "framework/SceneBase.h"

namespace Forradia
{

    class SceneServer : public SceneBase
    {
    public:
        using SceneBase::SceneBase;

        void Enter() override;
        void Update() override;
        void Render() override;
        void DoMouseDown(Uint8 mouseButton) override {};
        void DoMouseUp(Uint8 mouseButton) override {}
        void DoKeyDown(SDL_Keycode key) override {}
        void DoKeyUp(SDL_Keycode key) override {}
    };

}  // namespace Forradia
