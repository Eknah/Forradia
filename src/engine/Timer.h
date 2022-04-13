// Copyright (C) 2022  Andreas �kerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "Aliases.h"

namespace Forradia
{

    class Timer
    {

    public:
        Timer(UPtr<int> _duration) : durationPtr(std::move(_duration)) {}

        void Reset();
        bool HasFinished();
        int GetPassedTicks();

    private:

        UPtr<int> durationPtr = nullptr;
        int startTime = 0;

    };

}  // namespace Forradia
