// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "MouseHandler.h"

namespace Forradia {

void cMouseHandler::ResetForNewFrame() const {
    *wheelAmount *= 0.85f;

    if (std::abs(*wheelAmount) < 0.1f)
      *wheelAmount = 0;

    *leftButtonBeenFired = false;
    *rightButtonBeenFired = false;
  }

bool cMouseHandler::GetLeftButtonBeenFired() const  {
      return *leftButtonBeenFired;
  }

bool cMouseHandler::GetRightButtonBeenFired() const {
      return *rightButtonBeenFired;
  }

void cMouseHandler::SetLeftButtonBeenFired()  {
      *leftButtonBeenFired = true;
  }

void cMouseHandler::SetRightButtonBeenFired() {
      *rightButtonBeenFired = true;
  }

}  // namespace Forradia
