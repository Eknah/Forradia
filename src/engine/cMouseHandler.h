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

  UPtr<float> WheelAmount = MakeUPtr<float>(0.0f);
  bool LeftButtonDown = false;
  bool RightButtonDown = false;

 private:
  UPtr<bool> LeftButtonBeenFired = MakeUPtr<bool>(false);
  UPtr<bool> RightButtonBeenFired = MakeUPtr<bool>(false);
};

}  // namespace Forradia
