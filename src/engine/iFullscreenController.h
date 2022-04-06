// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

class iEngine;

class iFullscreenController {
 public:
  explicit iFullscreenController(const iEngine &_engine) : engine(_engine) {}

  virtual void UpdateFullscreenToggling() = 0;
  virtual void ToggleFullscreen() = 0;

 protected:
  const iEngine &engine;
  bool fullscreenOn = true;
};

}  // namespace Forradia
