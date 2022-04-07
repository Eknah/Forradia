// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Engine.h"
#include "../engine/Utilities.h"

namespace Forradia {

class cGuiMinimap {
 public:
  explicit cGuiMinimap(const cEngine &_engine) : engine(_engine) {}

  void Render();

 private:
  const cEngine &engine;

  const int minimapSize = 250;
  cPalette palette;
  cUtilities utilities;
};

}  // namespace Forradia
