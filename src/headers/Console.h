// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "Aliases.h"
#include "Engine.h"
#include "Utilities.h"
#include "FileSystem.h"

namespace Forradia
{
    class Console
    {
        // Functions
    public:

        explicit Console(Engine& _e)
		: e(_e), fileSystem(*this) {}

        void Update();
        void Render();
        void Print(String message);
        void ToggleInput();
        void Clear();
        void KeyDown(SDL_Keycode key);
        bool MouseDown(Uint8 mouseButton);

    private:
        bool InputBeginsWith(String text);
        RectF GetResizeIconBounds();
		
        Engine& e;

        const float width = 3 * 0.15f;
        const float height = 0.15f;
        const float margin = 0.005f;

        float inputLineHeight = 0.025f;

        String inputText;
        bool input_active = false;

        RectF bounds =
        {
            0.0f,
            1.0f - 0.03f - height,
            width,
            height
        };

        List<String> textBoxText = {};
        Utilities utils;
        FileSystem fileSystem;
        int resizeIconSize = 30;
    };
}