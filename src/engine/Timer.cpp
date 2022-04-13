// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Timer.h"
#include "../engine/Aliases.h"

namespace Forradia
{

    void Timer::Reset()
    {
        startTime = Ticks();
    }

    bool Timer::HasFinished()
    {
        return Ticks() > startTime + *durationPtr;
    }

    int Timer::GetPassedTicks()
    {
        return Ticks() - startTime;
    }

}  // namespace Forradia
