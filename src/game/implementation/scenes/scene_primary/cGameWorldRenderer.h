// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Engine.h"
#include "cBackground.h"
#include "cCamera.h"
#include "cPlanetShaper.h"

namespace Forradia {

class cGameWorldRenderer {
 public:
  cGameWorldRenderer(const cEngine &_engine, const cCamera &_camera)
      : engine(_engine), background(_engine), planetShaper(_engine),
        camera(_camera) {}

  void Render();

 private:
  void RenderTilesAndObjects();
  void RenderSunRaysAndActors();
  void RenderRoof();

  const cEngine &engine;
  cBackground background;
  const cCamera &camera;
  cPlanetShaper planetShaper;
  const int groundTypeWaterId = GetId("GroundTypeWater");
  const int groundTypeWaterAnimatedId[4] = {
    GetId("GroundTypeWater"),
    GetId("GroundTypeWater1"),
    GetId("GroundTypeWater2"),
    GetId("GroundTypeWater3")
  };
};

}  // namespace Forradia
