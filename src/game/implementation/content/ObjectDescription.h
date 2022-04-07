// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/eObjectFlags.h"

namespace Forradia {

class cObjectDescription {
 public:
  cObjectDescription() = default;
  explicit cObjectDescription(char _flags)
      : flags(_flags) {}

  // Description parameters
  char flags = ObjectNone;
  float opacity = 1.0f;
};

}  // namespace Forradia
