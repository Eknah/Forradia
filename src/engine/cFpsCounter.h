// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/iEngine.h"
#include "iFpsCounter.h"

namespace Forradia {

class cFpsCounter : public iFpsCounter {
 public:
  explicit cFpsCounter(iEngine &engine) : iFpsCounter(engine) {}

  void Update() override;

  void Render() override;
};

}  // namespace Forradia
