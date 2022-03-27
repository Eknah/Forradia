
#include "cGuiMinimap.h"
#include "../engine/cEngine.h"

namespace Forradia
{

void cGuiMinimap::Render()
{
    auto minimap_size_f = Utilities.ConvertToFloat(MinimapSize);

    Engine.FillRectangle(Palette.MediumBlue, 0, 0, minimap_size_f.Width, minimap_size_f.Height);
    Engine.DrawRectangle(Palette.Black, 0, 0, minimap_size_f.Width, minimap_size_f.Height);
}

}
