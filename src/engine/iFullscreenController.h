// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

class IEngine;

class IFullscreenController {
 public:
  explicit IFullscreenController(const IEngine &_engine) : engine(_engine) {}

  virtual void UpdateFullscreenToggling() = 0;
  virtual void ToggleFullscreen() = 0;

 protected:
  const IEngine &engine;
  bool fullscreenOn = true;
};

}  // namespace Forradia
