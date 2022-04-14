// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "scenePrimary/Camera.h"
#include "scenePrimary/WorldRenderer.h"
#include "scenePrimary/gui/Gui.h"

namespace Forradia
{

    class ScenePrimary : public SceneBase
    {

    public:

        explicit ScenePrimary(const Engine& _e) : SceneBase(_e), gui(_e), cam(_e), worldRenderer(_e, cam)
        {}

        void Enter() override;
        void Update() override;
        void Render() override;
        void DoMouseDown(Uint8 mouseButton) override;
        void DoMouseUp(Uint8 mouseButton) override;
        void DoKeyDown(SDL_Keycode key) override;
        void DoKeyUp(SDL_Keycode key) override {}

    private:

        Camera cam;
        Gui gui;
        Utilities utils;
        WorldRenderer worldRenderer;

    };

}  // namespace Forradia
