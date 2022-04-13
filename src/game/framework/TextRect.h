// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/RectF.h"
#include <string>
#include "../engine/Aliases.h"

namespace Forradia
{

    class TextRect
    {
    public:
        RectF bounds = { 0, 0, 0, 0 };
        String text;
    };

}  // namespace Forradia
