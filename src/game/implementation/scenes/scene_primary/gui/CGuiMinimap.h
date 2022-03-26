#pragma once
#include "../core/CEngine.h"
#include "../core/CUtilities.h"

namespace Forradia
{

class CGuiMinimap
{

public:

    CGuiMinimap(CEngine& engine) : Engine(engine) {}

    void Render();

private:

    CEngine& Engine;

    const int MinimapSize = 250;
    CPalette Palette;
    CUtilities Utilities;
};

}
