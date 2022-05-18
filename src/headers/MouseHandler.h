// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "Aliases.h"
#include "Point2F.h"

namespace Forradia
{

    class MouseHandler
    {
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
        Point2F leftDownPos = {-1, -1};
        Point2F rightDownPos = {-1, -1};
        float leftClickDeltaPos = 0;
        float rightClickDeltaPos = 0;

    private:
        UPtr<bool> leftButtonBeenFired = MakeUPtr<bool>(false);
        UPtr<bool> rightButtonBeenFired = MakeUPtr<bool>(false);
    };

}