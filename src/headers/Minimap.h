// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "Engine.h"
#include "Utilities.h"

namespace Forradia
{

    class Minimap
    {

    public:

        explicit Minimap(const Engine& _e) : e(_e) {}

        void Render();

    private:

        const Engine& e;

        const int minimapSize = 250;
        Utilities utils;

    };

}  // namespace Forradia
