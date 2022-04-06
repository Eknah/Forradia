// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cRandom.h"

namespace Forradia {

class cEngine;

class cMobsEngine {
 public:
  explicit cMobsEngine(const cEngine &_engine) : engine(_engine) {}

  void Update();

 private:
  const cEngine &engine;

  cRandom random;
};

}  // namespace Forradia
