// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Random.h"

namespace Forradia {

class Engine;

class MobsEngine {
 public:
  explicit MobsEngine(const Engine &_e) : e(_e) {}

  void Update();

 private:
  const Engine &e;

  Random random;
};

}  // namespace Forradia
