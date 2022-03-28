// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <utility>
#include "iSceneManager.h"

namespace Forradia {

class cSceneManager : public iSceneManager {
 public:
    explicit cSceneManager(const iEngine &engine) :
          iSceneManager(engine) {}

  inline void Initialize(cScenesCollection scenes,
                         int startScene) override {
    ScenesCollection = std::move(scenes);
    *CurrentScene = startScene;
  }

  inline UPtr<cSceneBase> &GetCurrentScene() override {
    return ScenesCollection.Scenes.at(*CurrentScene);
  }

  inline void SwitchToScene(
          std::string newScene) const override {
    *CurrentScene = GetId(newScene);
    ScenesCollection.Scenes.at(*CurrentScene)->Enter();
    Engine.GameLoop.ResetForNewFrame();
  }
};

}  // namespace Forradia
