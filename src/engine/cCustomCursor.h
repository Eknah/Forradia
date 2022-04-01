// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "iCustomCursor.h"
#include "iEngine.h"

namespace Forradia {

class cCustomCursor : public iCustomCursor {
 public:
  explicit cCustomCursor(iEngine &engine) : iCustomCursor(engine) {}

  void Initialize() override;

  void ResetForNewFrame() override;

  void Render() override;
};

}  // namespace Forradia
