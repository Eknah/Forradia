// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

class iEngine;

class iGameLoop {
 public:
  explicit iGameLoop(iEngine &engine) : Engine(engine) {}

  virtual void Run() = 0;

  // Looped functions
  virtual void Update() = 0;
  virtual void Render() = 0;
  virtual void ResetForNewFrame() = 0;

 protected:
  iEngine &Engine;
};

}  // namespace Forradia
