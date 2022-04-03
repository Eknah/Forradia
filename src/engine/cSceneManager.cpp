// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cSceneManager.h"

namespace Forradia {

void cSceneManager::Initialize(cScenesCollection scenes,
                         int startScene) {
    ScenesCollection = std::move(scenes);
    *CurrentScene = startScene;
  }

SPtr<cSceneBase> &cSceneManager::GetCurrentScene() {
    return ScenesCollection.scenes.at(*CurrentScene);
  }

void cSceneManager::SwitchToScene(
          std::string newScene) const {
    *CurrentScene = GetId(newScene);
    ScenesCollection.scenes.at(*CurrentScene)->Enter();
    Engine.gameLoop.ResetForNewFrame();
  }

}  // namespace Forradia
