// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "Aliases.h"

namespace Forradia {

class cMouseHandler {
 public:
  // Game loop related

  void ResetForNewFrame() const;

  bool GetLeftButtonBeenFired() const;

  bool GetRightButtonBeenFired() const;

  void SetLeftButtonBeenFired();

  void SetRightButtonBeenFired();

  UPtr<float> wheelAmount = MakeUPtr<float>(0.0f);
  bool leftButtonDown = false;
  bool rightButtonDown = false;

 private:
  UPtr<bool> leftButtonBeenFired = MakeUPtr<bool>(false);
  UPtr<bool> rightButtonBeenFired = MakeUPtr<bool>(false);
};

}  // namespace Forradia
