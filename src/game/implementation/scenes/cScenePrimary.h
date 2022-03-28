// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "CommonExternal.h"
#include "scene_primary/cCamera.h"
#include "scene_primary/cGameWorldRenderer.h"
#include "scene_primary/cMobsEngine.h"
#include "scene_primary/gui/cGui.h"

namespace Forradia {

class cScenePrimary : public cSceneBase {
 public:
  cScenePrimary(const cEngine &Engine_)
      : cSceneBase(Engine_), Gui(Engine_), Camera(Engine_), MobsEngine(Engine_),
        GameWorldRenderer(Engine_, Camera) {}

  void Enter() override;
  void Update() override;
  void Render() override;
  void DoMouseDown(Uint8 MouseButton) override;
  void DoMouseUp(Uint8 MouseButton) override;

 private:
  cCamera Camera;
  cGui Gui;
  cUtilities Utilities;
  cMobsEngine MobsEngine;
  cGameWorldRenderer GameWorldRenderer;
};

}  // namespace Forradia
