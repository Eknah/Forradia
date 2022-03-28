// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "CommonExternal.h"
#include "cUtilities.h"
#include "eCursorTypes.h"

namespace Forradia
{

class iEngine;

class iCustomCursor
{
public:

    iCustomCursor(iEngine& engine) : Engine(engine) {}

    virtual inline void Initialize() = 0;
    virtual inline void ResetForNewFrame() = 0;
    virtual inline void Render() = 0;

    eCursorTypes CursorType = eCursorTypes::Default;

protected:

    iEngine& Engine;
    cUtilities Utilities;

    int CursorSize = 20;

};

}
