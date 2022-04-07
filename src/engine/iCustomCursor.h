// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "Utilities.h"
#include "eCursorTypes.h"

namespace Forradia {

class iEngine;

class iCustomCursor {
 public:
  explicit iCustomCursor(iEngine &_engine) : engine(_engine) {}

  virtual void Initialize() = 0;
  virtual void ResetForNewFrame() = 0;
  virtual void Render() = 0;

  eCursorTypes cursorType = eCursorTypes::Default;

 protected:
  iEngine &engine;
  cUtilities utilities;

  int cursorSize = 40;
};

}  // namespace Forradia
