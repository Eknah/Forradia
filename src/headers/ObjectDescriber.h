// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "ObjectFlags.h"

namespace Forradia
{

    class ObjectDescriber
    {

    public:

        ObjectDescriber() = default;
        explicit ObjectDescriber(char _flags) : flags(_flags) {}

        char flags = FlagNone;
        float opacity = 1.0f;

    };

}