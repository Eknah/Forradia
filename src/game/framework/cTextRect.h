// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cRectF.h"
#include <string>

namespace Forradia {


class cTextRect {
 public:
    cRectF Bounds = {0, 0, 0, 0};
    std::string Text;
};

}  // namespace Forradia
