// Copyright (C) 2022  Andreas Åkerberg

#pragma once
#include "../engine/cUtilities.h"
#include "framework/cGuiWindowBase.h"

namespace Forradia
{

class cGuiWindowInventory : public cGuiWindowBase
{

public:

    using       cGuiWindowBase::cGuiWindowBase;

    void        RenderDerived() override;
    void        DoMouseDownDerived(Uint8 MouseButton) override;

private:

    const int   NumSlotCols = 4;

    cUtilities  Utilities;
    cPalette    Palette;
};

}
