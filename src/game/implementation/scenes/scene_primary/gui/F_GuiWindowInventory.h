
#pragma once
#include "../core/F_Utilities.h"
#include "framework/F_GuiWindowBase.h"

namespace Forradia
{

class F_GuiWindowInventory : public F_GuiWindowBase
{

public:

    using F_GuiWindowBase::F_GuiWindowBase;

    void RenderDerived() override;
    void DoMouseDownDerived(Uint8 mouseButton) override;

private:

    const int NumSlotCols = 4;

    F_Utilities Utilities;
    F_Palette Palette;
};

}
