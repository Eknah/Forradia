// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <memory>
#include "Aliases.h"
#include "SDL_Deleter.h"
#include "Utilities.h"
#include <vector>

namespace Forradia
{

class DrawStringOperation
{
public:
    DrawStringOperation(std::string _text, SDL_Color _color, float _x, float _y, bool _centerAlign, float _specificScaling) :
    text(_text), color(_color), x(_x), y(_y), centerAlign(_centerAlign), specificScaling(_specificScaling)
    {}

    std::string text;
    SDL_Color color;
    float x;
    float y;
    bool centerAlign;
    float specificScaling;
};

    class TextGraphics
    {
    public:
        void Init();

        // --- Drawing operations ---

        void DrawString(std::string text, SDL_Color color, Point2F point, bool centerAlign = false, float specificScaling = 1.0f);
        void DrawString(std::string text, SDL_Color color, float x, float y, bool centerAlign = false, float specificScaling = 1.0f);
        void DrawStringActual(std::string text, SDL_Color color, float x, float y, bool centerAlign = false, float specificScaling = 1.0f) const;
        void RenderAllStrings();

    private:
        const std::string defaultFontPath = "/Resources/Fonts/PixeloidSans.ttf";
        const int defaultFontSize = 20;
        const float scaling = 0.8f;

        std::vector<DrawStringOperation> drawStringOperations;

        std::unique_ptr<TTF_Font, SDL_Deleter> defaultFont;
        Utilities utils;
    };

}  // namespace Forradia
