#pragma once
#include "../Hidden/CUtilities.h"
#include "Framework/CGuiWindowBase.h"

namespace Forradia
{

class CGuiWindowInventory : public CGuiWindowBase
{

public:

    using CGuiWindowBase::CGuiWindowBase;

    void RenderDerived() override;
    void DoMouseDownDerived(Uint8 mouseButton) override;

private:

    const int NumSlotCols = 4;

    CUtilities Utilities;
    CPalette Palette;
};

}
