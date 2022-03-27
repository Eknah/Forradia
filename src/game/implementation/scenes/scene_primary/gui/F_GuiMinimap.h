
#pragma once
#include "../engine/F_Engine.h"
#include "../engine/F_Utilities.h"

namespace Forradia
{

class F_GuiMinimap
{

public:

    F_GuiMinimap(F_Engine& engine) : Engine(engine) {}

    void Render();

private:

    F_Engine& Engine;

    const int MinimapSize = 250;
    F_Palette Palette;
    F_Utilities Utilities;
};

}
