// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Minimap.h"
#include "../engine/Engine.h"

namespace Forradia
{

    void Minimap::Render()
    {
        auto minimapSizeF = utils.ConvertToFloat(minimapSize);

        e.FillRect(pal.gray, 0, 0, minimapSizeF.w, minimapSizeF.h);
        e.DrawRect(pal.black, 0, 0, minimapSizeF.w, minimapSizeF.h);
    }

}  // namespace Forradia
