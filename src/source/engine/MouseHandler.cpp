// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "MouseHandler.h"

namespace Forradia
{

    void MouseHandler::ResetForNewFrame() const
    {
        *wheelAmount *= 0.85f;

        if (std::abs(*wheelAmount) < 0.1f)
            *wheelAmount = 0;

        *leftButtonBeenFired = false;
        *rightButtonBeenFired = false;
    }

    bool MouseHandler::GetLeftButtonBeenFired() const
    {
        return *leftButtonBeenFired;
    }

    bool MouseHandler::GetRightButtonBeenFired() const
    {
        return *rightButtonBeenFired;
    }

    void MouseHandler::SetLeftButtonBeenFired()
    {
        *leftButtonBeenFired = true;
    }

    void MouseHandler::SetRightButtonBeenFired()
    {
        *rightButtonBeenFired = true;
    }

}