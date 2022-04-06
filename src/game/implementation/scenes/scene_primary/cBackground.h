// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

class cEngine;

class cBackground {
 public:
  explicit cBackground(const cEngine &_engine) : engine(_engine) {}

  void Render(float zoom);

 private:
  const cEngine &engine;
};

}  // namespace Forradia
