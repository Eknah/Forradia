// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

class Engine;

class Background {
 public:
  explicit Background(const Engine &_engine) : engine(_engine) {}

  void Render(float zoom);

 private:
  const Engine &engine;
};

}  // namespace Forradia
