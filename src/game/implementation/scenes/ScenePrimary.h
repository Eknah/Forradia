// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "scenePrimary/Camera.h"
#include "scenePrimary/GameWorldRenderer.h"
#include "scenePrimary/MobsEngine.h"
#include "scenePrimary/gui/Gui.h"

namespace Forradia {

class ScenePrimary : public SceneBase {
 public:
  explicit ScenePrimary(const Engine &_e)
      : SceneBase(_e), gui(_e), camera(_e), mobsEngine(_e),
        gameWorldRenderer(_e, camera) {}

  void Enter() override;
  void Update() override;
  void Render() override;
  void DoMouseDown(Uint8 mouseButton) override;
  void DoMouseUp(Uint8 mouseButton) override;

 private:
  Camera camera;
  Gui gui;
  Utilities utilities;
  MobsEngine mobsEngine;
  GameWorldRenderer gameWorldRenderer;
};

}  // namespace Forradia
