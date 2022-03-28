// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

class cObjectDescription {
 public:
  cObjectDescription() = default;
  cObjectDescription(bool Moveable_, bool BlocksMovement_, bool BlocksSight_)
      : Movable(Moveable_), BlocksMovement(BlocksMovement_),
        BlocksSight(BlocksSight_) {}

  // Description parameters

  bool Movable = false;
  bool BlocksMovement = false;
  bool BlocksSight = false;
};

} // namespace Forradia
