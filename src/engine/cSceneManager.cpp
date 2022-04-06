// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cSceneManager.h"

namespace Forradia {

void cSceneManager::Initialize(cScenesCollection scenes,
                         int startScene) {
    scenesCollection = std::move(scenes);
    *currentScene = startScene;
  }

SPtr<cSceneBase> &cSceneManager::GetCurrentScene() {
    return scenesCollection.scenes.at(*currentScene);
  }

void cSceneManager::SwitchToScene(
          std::string newScene) const {
    *currentScene = GetId(newScene);
    scenesCollection.scenes.at(*currentScene)->Enter();
    engine.gameLoop.ResetForNewFrame();
  }

}  // namespace Forradia
