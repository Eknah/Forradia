
#pragma once
#include "CommonExternal.h"
#include "F_Utilities.h"
#include "F_ECursorTypes.h"

namespace Forradia
{

class F_IEngine;

class F_ICustomCursor
{
public:

    F_ICustomCursor(F_IEngine& engine) : Engine(engine) {}

    virtual inline void Initialize() = 0;
    virtual inline void ResetForNewFrame() = 0;
    virtual inline void Render() = 0;

    F_ECursorTypes CursorType = F_ECursorTypes::Default;

protected:

    F_IEngine& Engine;
    F_Utilities Utilities;

    int CursorSize = 20;

};

}
