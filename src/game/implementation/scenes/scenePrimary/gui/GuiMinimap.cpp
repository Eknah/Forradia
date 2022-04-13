// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "GuiMinimap.h"
#include "../engine/Engine.h"

namespace Forradia
{

    void GuiMinimap::Render()
    {
        auto minimapSizeF = utils.ConvertToFloat(minimapSize);

        e.FillRectangle(palette.mediumBlueSemiTrans, 0, 0, minimapSizeF.width,
            minimapSizeF.height);
        e.DrawRectangle(palette.black, 0, 0, minimapSizeF.width,
            minimapSizeF.height);
    }

}  // namespace Forradia
