// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

enum eObjectFlags : char {
    ObjectNone = 0,
    ObjectMovementBlock = 1,
    ObjectMovable = 2,
    ObjectNoShadow = 4
};

}  // namespace Forradia
