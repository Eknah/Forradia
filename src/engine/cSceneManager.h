// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <utility>
#include "iEngine.h"
#include "iSceneManager.h"

namespace Forradia {

class cSceneManager : public iSceneManager {
 public:
    explicit cSceneManager(const iEngine &engine) :
          iSceneManager(engine) {}

  void Initialize(cScenesCollection scenes,
                         int startScene) override;

  SPtr<cSceneBase> &GetCurrentScene() override;

  void SwitchToScene(
          std::string newScene) const override;
};

}  // namespace Forradia
