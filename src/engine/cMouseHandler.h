// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "Aliases.h"
#include "CommonExternal.h"

namespace Forradia {

class cMouseHandler {
 public:
  // Game loop related

  inline void ResetForNewFrame() const {
    *WheelAmount *= 0.85f;

    if (std::abs(*WheelAmount) < 0.1f)
      *WheelAmount = 0;

    *LeftButtonBeenFired = false;
    *RightButtonBeenFired = false;
  }

  inline bool GetLeftButtonBeenFired() const  {
      return *LeftButtonBeenFired;
  }

  inline bool GetRightButtonBeenFired() const {
      return *RightButtonBeenFired;
  }

  inline void SetLeftButtonBeenFired()  {
      *LeftButtonBeenFired = true;
  }

  inline void SetRightButtonBeenFired() {
      *RightButtonBeenFired = true;
  }

  UPtr<float> WheelAmount = MakeUPtr<float>(0.0f);
  bool LeftButtonDown = false;
  bool RightButtonDown = false;

 private:
  UPtr<bool> LeftButtonBeenFired = MakeUPtr<bool>(false);
  UPtr<bool> RightButtonBeenFired = MakeUPtr<bool>(false);

};

}  // namespace Forradia
