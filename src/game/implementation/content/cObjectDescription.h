// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/eObjectFlags.h"

namespace Forradia {

class cObjectDescription {
 public:
  cObjectDescription() = default;
  explicit cObjectDescription(char Flags_)
      : Flags(Flags_) {}

  // Description parameters
  char Flags = ObjectNone;
  float Opacity = 1.0f;
};

}  // namespace Forradia
