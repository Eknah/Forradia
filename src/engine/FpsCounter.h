// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/IEngine.h"
#include "IFpsCounter.h"

namespace Forradia {

class FpsCounter : public IFpsCounter {
 public:
  explicit FpsCounter(IEngine &e) : IFpsCounter(e) {}

  void Update() override;

  void Render() override;
};

}  // namespace Forradia
