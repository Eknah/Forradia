// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "scenePrimary/Camera.h"
#include "scenePrimary/GameWorldRenderer.h"
#include "scenePrimary/MobsEngine.h"
#include "scenePrimary/gui/Gui.h"

namespace Forradia {

class cScenePrimary : public cSceneBase {
 public:
  explicit cScenePrimary(const cEngine &_engine)
      : cSceneBase(_engine), gui(_engine), camera(_engine), mobsEngine(_engine),
        gameWorldRenderer(_engine, camera) {}

  void Enter() override;
  void Update() override;
  void Render() override;
  void DoMouseDown(Uint8 mouseButton) override;
  void DoMouseUp(Uint8 mouseButton) override;

 private:
  cCamera camera;
  cGui gui;
  cUtilities utilities;
  cMobsEngine mobsEngine;
  cGameWorldRenderer gameWorldRenderer;
};

}  // namespace Forradia
