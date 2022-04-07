// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Utilities.h"
#include "framework/cGuiWindowBase.h"

namespace Forradia {

class cGuiWindowMall : public cGuiWindowBase {
 public:
  using cGuiWindowBase::cGuiWindowBase;

  void RenderDerived() override;
  void DoMouseDownDerived(Uint8 mouseButton) override;

 private:
  cUtilities utilities;
  cPalette palette;
};

}  // namespace Forradia
