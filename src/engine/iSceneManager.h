// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "CommonExternal.h"
#include "cScenesCollection.h"

namespace Forradia {

class iEngine;

class iSceneManager {
 public:
  explicit iSceneManager(const iEngine &engine) : Engine(engine) {}

  virtual inline void Initialize(cScenesCollection scenes, int startScene) = 0;

  virtual inline UPtr<cSceneBase> &GetCurrentScene() = 0;

  virtual inline void SwitchToScene(std::string newScene) const = 0;
 protected:
  const iEngine &Engine;
  cScenesCollection ScenesCollection;
  const UPtr<int> CurrentScene = MakeUPtr<int>(-1);
};

}  // namespace Forradia
