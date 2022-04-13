// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

enum ObjectFlags : char {
    FlagNone = 0,
    FlagObstacle = 1,
    FlagMovable = 2,
    FlagNoShadow = 4
};

}  // namespace Forradia
