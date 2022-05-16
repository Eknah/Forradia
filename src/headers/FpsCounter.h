// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "IEngine.h"
#include "IFpsCounter.h"
#include "Timer.h"

namespace Forradia
{

    class FpsCounter : public IFpsCounter
    {
    public:
        explicit FpsCounter(IEngine& e) : IFpsCounter(e) {}

        void Update() override;

        void Render() override;

    private:
        Timer timer = Timer(MakeUPtr<int>(1000));

    };

}  // namespace Forradia
