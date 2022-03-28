// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cGuiMinimap.h"
#include "../engine/cEngine.h"

namespace Forradia {

void cGuiMinimap::Render() {
  auto MinimapSizeF = Utilities.ConvertToFloat(MinimapSize);

  Engine.FillRectangle(Palette.MediumBlue, 0, 0, MinimapSizeF.Width,
                       MinimapSizeF.Height);
  Engine.DrawRectangle(Palette.Black, 0, 0, MinimapSizeF.Width,
                       MinimapSizeF.Height);
}

} // namespace Forradia
