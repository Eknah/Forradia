// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include "Utilities.h"
#include "SceneBase.h"
#include "Engine.h"

namespace Forradia
{
    class SceneGameStart : public SceneBase
    {
    public:
        SceneGameStart(
			Engine& _e,
			std::string _imageNameBackground,
			std::string _imageNameLogo,
			std::string _text,
			std::string _switchToSceneName
		)
		: SceneBase(_e),
		switchToSceneName(_switchToSceneName),
		imageNameBackground(_imageNameBackground),
		imageNameLogo(_imageNameLogo),
		text(_text) {}

        void Enter() override {}
        void Update() override {}
        void Render() override;
        void MouseDown(Uint8 mouseButton);
        void MouseUp(Uint8 mouseButton) override {}
        void KeyDown(SDL_Keycode key);
        void KeyUp(SDL_Keycode key) override {}

    private:
        std::string switchToSceneName;
        std::string imageNameBackground;
        std::string imageNameLogo;
        std::string text;
    };
}