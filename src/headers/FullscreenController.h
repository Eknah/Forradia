// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "IEngine.h"
#include "IFullscreenController.h"

namespace Forradia
{
    class FullscreenController : public IFullscreenController
    {
    public:
        explicit FullscreenController(const IEngine& e)
		: IFullscreenController(e) {}

        void UpdateFullscreenToggling() override;
        void ToggleFullscreen() override;
    };
}