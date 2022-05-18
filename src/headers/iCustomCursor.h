// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "Utilities.h"
#include "CursorTypes.h"

namespace Forradia
{
    class IEngine;

    class ICustomCursor
    {
    public:
        explicit ICustomCursor(IEngine& _e)
		: e(_e) {}

        virtual void Init() = 0;
        virtual void ResetForNewFrame() = 0;
        virtual void Render() = 0;

        CursorTypes type = CursorTypes::Default;
		
    protected:
        IEngine& e;
        Utilities utils;
        int cursorSize = 40;
    };
}