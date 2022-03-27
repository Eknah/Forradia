
#pragma once
#include "../engine/cEngine.h"
#include "../engine/cUtilities.h"

namespace Forradia
{

class cGuiMinimap
{

public:

    cGuiMinimap(cEngine& Engine_) : Engine(Engine_) {}

    void Render();

private:

    cEngine& Engine;

    const int MinimapSize = 250;
    cPalette Palette;
    cUtilities Utilities;
};

}
