// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/eObjectFlags.h"

namespace Forradia {

class cObjectDescription {
 public:
  cObjectDescription() = default;
  explicit cObjectDescription(eObjectFlags Flags_)
      : Flags(Flags_) {}

  // Description parameters
  eObjectFlags Flags = ObjectNone;
};

}  // namespace Forradia
