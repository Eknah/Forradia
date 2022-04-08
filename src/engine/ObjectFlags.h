// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

enum ObjectFlags : char {
    ObjNone = 0,
    ObjObstacle = 1,
    ObjMovable = 2,
    ObjNoShadow = 4
};

}  // namespace Forradia
