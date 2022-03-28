// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

class cEngine;

class cBackground {
 public:
  cBackground(const cEngine &Engine_) : Engine(Engine_) {}

  void Render(float Zoom);

 private:
  const cEngine &Engine;
};

}  // namespace Forradia
