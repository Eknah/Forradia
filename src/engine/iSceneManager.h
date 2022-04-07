// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "ScenesCollection.h"

namespace Forradia {

class iEngine;

class iSceneManager {
 public:
  explicit iSceneManager(const iEngine &_engine) : engine(_engine) {}

  virtual void Initialize(cScenesCollection _scenes, int startScene) = 0;

  virtual SPtr<cSceneBase> &GetCurrentScene() = 0;

  virtual void SwitchToScene(std::string newScene) const = 0;
 protected:
  const iEngine &engine;
  cScenesCollection scenesCollection;
  const UPtr<int> currentScene = MakeUPtr<int>(-1);
};

}  // namespace Forradia
