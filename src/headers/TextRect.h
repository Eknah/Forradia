// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "RectF.h"
#include <string>
#include "Aliases.h"

namespace Forradia
{

    class TextRect
    {

        // Members

    public:

        RectF bounds = { 0, 0, 0, 0 };
        String text;

    };

}  // namespace Forradia
