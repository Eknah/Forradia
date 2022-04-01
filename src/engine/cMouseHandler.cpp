// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cMouseHandler.h"

namespace Forradia {

void cMouseHandler::ResetForNewFrame() const {
    *WheelAmount *= 0.85f;

    if (std::abs(*WheelAmount) < 0.1f)
      *WheelAmount = 0;

    *LeftButtonBeenFired = false;
    *RightButtonBeenFired = false;
  }

bool cMouseHandler::GetLeftButtonBeenFired() const  {
      return *LeftButtonBeenFired;
  }

bool cMouseHandler::GetRightButtonBeenFired() const {
      return *RightButtonBeenFired;
  }

void cMouseHandler::SetLeftButtonBeenFired()  {
      *LeftButtonBeenFired = true;
  }

void cMouseHandler::SetRightButtonBeenFired() {
      *RightButtonBeenFired = true;
  }

}  // namespace Forradia
