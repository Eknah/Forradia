// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "ICustomCursor.h"
#include "IEngine.h"

namespace Forradia {

class CustomCursor : public ICustomCursor {
 public:
  explicit CustomCursor(IEngine &engine) : ICustomCursor(engine) {}

  void Initialize() override;

  void ResetForNewFrame() override;

  void Render() override;
};

}  // namespace Forradia
