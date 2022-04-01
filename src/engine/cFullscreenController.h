// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "iEngine.h"
#include "iFullscreenController.h"

namespace Forradia {

class cFullscreenController : public iFullscreenController {
 public:
  explicit cFullscreenController(const iEngine &engine) :
        iFullscreenController(engine) {}

  void UpdateFullscreenToggling() override;

  void ToggleFullscreen() override;
};

}  // namespace Forradia
