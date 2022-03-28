// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <utility>
#include "cScenesCollection.h"
#include "framework/cSceneBase.h"

namespace Forradia {

class cSceneManager {
 public:
  inline void Initialize(cScenesCollection scenes, int startScene) {
    ScenesCollection = std::move(scenes);
    *CurrentScene.get() = startScene;
  }

  inline UPtr<cSceneBase> &GetCurrentScene() {
    return ScenesCollection.Scenes.at(*CurrentScene);
  }

  inline void SwitchToScene(std::string newScene) const {
    *CurrentScene.get() = GetId(newScene);
    ScenesCollection.Scenes.at(*CurrentScene)->Enter();
  }

 private:
  cScenesCollection ScenesCollection;
  const UPtr<int> CurrentScene = MakeUPtr<int>(-1);
};

}  // namespace Forradia
