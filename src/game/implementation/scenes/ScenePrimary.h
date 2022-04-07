// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "scene_primary/Camera.h"
#include "scene_primary/GameWorldRenderer.h"
#include "scene_primary/MobsEngine.h"
#include "scene_primary/gui/Gui.h"

namespace Forradia {

class cScenePrimary : public cSceneBase {
 public:
  explicit cScenePrimary(const cEngine &_engine)
      : cSceneBase(_engine), gui(_engine), camera(_engine), mobsEngine(_engine),
        gameWorldRenderer(_engine, camera) {}

  void Enter() override;
  void Update() override;
  void Render() override;
  void DoMouseDown(Uint8 MouseButton) override;
  void DoMouseUp(Uint8 MouseButton) override;

 private:
  cCamera camera;
  cGui gui;
  cUtilities utilities;
  cMobsEngine mobsEngine;
  cGameWorldRenderer gameWorldRenderer;
};

}  // namespace Forradia
