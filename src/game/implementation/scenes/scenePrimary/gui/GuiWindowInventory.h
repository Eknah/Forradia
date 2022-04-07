// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Utilities.h"
#include "framework/GuiWindowBase.h"

namespace Forradia {

class cGuiWindowInventory : public cGuiWindowBase {
 public:
  using cGuiWindowBase::cGuiWindowBase;

  void RenderDerived() override;
  void DoMouseDownDerived(Uint8 mouseButton) override;

 private:
  const int numSlotCols = 4;

  cUtilities utilities;
  cPalette palette;
};

}  // namespace Forradia
