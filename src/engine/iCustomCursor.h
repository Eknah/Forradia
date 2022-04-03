// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "cUtilities.h"
#include "eCursorTypes.h"

namespace Forradia {

class iEngine;

class iCustomCursor {
 public:
  explicit iCustomCursor(iEngine &engine_) : engine(engine_) {}

  virtual void Initialize() = 0;
  virtual void ResetForNewFrame() = 0;
  virtual void Render() = 0;

  eCursorTypes cursorType = eCursorTypes::Default;

 protected:
  iEngine &engine;
  cUtilities utilities;

  int cursorSize = 20;
};

}  // namespace Forradia
