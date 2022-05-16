// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include "Point2.h"

namespace Forradia
{

    class CraftRecipe
    {

        // Members

    public:

        int toolObjectType = -1;
        int rawMatObjectType = -1;
        int resultObjectType = -1;
        std::string description;
        Point2 craftTile = {-1, -1};

    };

}  // namespace Forradia
