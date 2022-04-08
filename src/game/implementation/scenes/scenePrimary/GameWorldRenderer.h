// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Engine.h"
#include "Background.h"
#include "Camera.h"
#include "PlanetShaper.h"

namespace Forradia {

class GameWorldRenderer {
 public:
  GameWorldRenderer(const Engine &_engine, const Camera &_camera)
      : engine(_engine), background(_engine), planetShaper(_engine),
        camera(_camera) {}

  void Render();

 private:
  void RenderTilesAndObjects();
  void RenderSunRaysAndActors();
  void RenderRoof();

  const Engine &engine;
  Background background;
  const Camera &camera;
  PlanetShaper planetShaper;
  const int groundTypeWaterId = GetId("GroundTypeWater");
  const int groundTypeWaterAnimatedId[4] = {
    GetId("GroundTypeWater"),
    GetId("GroundTypeWater1"),
    GetId("GroundTypeWater2"),
    GetId("GroundTypeWater3")
  };
};

}  // namespace Forradia
