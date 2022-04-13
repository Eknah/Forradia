// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once


namespace Forradia
{

    class Timer
    {

    public:
        Timer(int _duration) : duration(_duration) {}

        void Reset();
        bool HasFinished();
        int GetPassedTicks();

    private:

        int duration = 0;
        int startTime = 0;

    };

}  // namespace Forradia
