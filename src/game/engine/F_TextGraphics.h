#pragma once
#include "CommonExternal.h"
#include "../core/F_SDL_Deleter.h"
#include "../core/Aliases.h"
#include "../core/F_Utilities.h"

namespace Forradia
{

class F_Engine;

class F_TextGraphics
{

public:

    F_TextGraphics(F_Engine& engine) : Engine(engine) {}

    void Initialize();

    // Drawing operations
    void DrawString(std::string message, SDL_Color color, float x, float y, bool centerAlign = false);

private:

    const std::string DefaultFontPath = "/Resources/Fonts/PixeloidSans.ttf";
    const int DefaultFontSize = 20;
    const float Scaling = 0.8f;

    F_Engine& Engine;
    std::unique_ptr<TTF_Font, F_SDL_Deleter> DefaultFont;
    F_Utilities Utilities;

};

}
