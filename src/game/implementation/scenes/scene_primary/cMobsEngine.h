// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cRandom.h"

namespace Forradia {

class cEngine;

class cMobsEngine {
 public:
  explicit cMobsEngine(const cEngine &Engine_) : Engine(Engine_) {}

  void Update();

 private:
  const cEngine &Engine;

  cRandom Random;
};

}  // namespace Forradia
