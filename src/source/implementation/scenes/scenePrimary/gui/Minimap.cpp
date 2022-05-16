// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Minimap.h"
#include "Engine.h"

namespace Forradia
{

    void Minimap::Render()
    {
        using namespace Palette;

        auto minimapSizeF = utils.ConvertToFloat(minimapSize);

        _ FillRect(MediumBlueSemiTrans, 0, 0, minimapSizeF.w, minimapSizeF.h);
        _ DrawRect(Black, 0, 0, minimapSizeF.w, minimapSizeF.h);
    }

}  // namespace Forradia
