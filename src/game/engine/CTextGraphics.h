#pragma once
#include "CommonExternal.h"
#include "../core/CSDL_Deleter.h"
#include "../core/Aliases.h"
#include "../core/CUtilities.h"

namespace Forradia
{

class CEngine;

class CTextGraphics
{

public:

    CTextGraphics(CEngine& engine) : Engine(engine) {}

    void Initialize();

    // Drawing operations
    void DrawString(std::string message, SDL_Color color, float x, float y, bool centerAlign = false);

private:

    const std::string DefaultFontPath = "/Resources/Fonts/PixeloidSans.ttf";
    const int DefaultFontSize = 20;
    const float Scaling = 0.8f;

    CEngine& Engine;
    std::unique_ptr<TTF_Font, CSDL_Deleter> DefaultFont;
    CUtilities Utilities;

};

}
