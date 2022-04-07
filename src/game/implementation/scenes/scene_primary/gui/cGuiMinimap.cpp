// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cGuiMinimap.h"
#include "../engine/Engine.h"

namespace Forradia {

void cGuiMinimap::Render() {
  auto MinimapSizeF = utilities.ConvertToFloat(minimapSize);

  engine.FillRectangle(palette.mediumBlue, 0, 0, MinimapSizeF.width,
                       MinimapSizeF.height);
  engine.DrawRectangle(palette.black, 0, 0, MinimapSizeF.width,
                       MinimapSizeF.height);
}

}  // namespace Forradia
