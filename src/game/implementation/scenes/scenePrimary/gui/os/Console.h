// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"
#include "../engine/Engine.h"
#include "../engine/Utilities.h"
#include "FileSystem.h"

namespace Forradia
{

    class Console
    {

    public:

        explicit Console(const Engine& _e) : e(_e), fileSystem(*this)
        {}

        void Render();
        void Print(String message);
        void ToggleInput();
        void Clear();
        void DoKeyDown(SDL_Keycode key);

    private:
        
        bool InputBeginsWith(String text);

        const Engine& e;

        const float width = 3 * 0.15f;
        const float height = 0.15f;
        const float margin = 0.005f;

        float inputLineHeight = 0.025f;

        String inputText;
        bool inputActive = false;

        RectF bounds =
        {
            0.5f - width / 2,
            1.0f - 0.03f - height,
            width,
            height
        };

        List<String> textBoxText = {};
        Utilities utils;
        FileSystem fileSystem;
        Palette palette;

    };

}  // namespace Forradia
