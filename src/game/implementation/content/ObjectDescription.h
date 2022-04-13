// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/ObjectFlags.h"

namespace Forradia
{

    class ObjectDescription
    {
    public:
        ObjectDescription() = default;
        explicit ObjectDescription(char _flags) : flags(_flags)
        {}

        // Description parameters
        char flags = ObjNone;
        float opacity = 1.0f;
    };

}  // namespace Forradia
