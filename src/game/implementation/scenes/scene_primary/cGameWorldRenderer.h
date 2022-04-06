// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cEngine.h"
#include "cBackground.h"
#include "cCamera.h"
#include "cPlanetShaper.h"

namespace Forradia {

class cGameWorldRenderer {
 public:
  cGameWorldRenderer(const cEngine &Engine_, const cCamera &Camera_)
      : Engine(Engine_), Background(Engine_), PlanetShaper(Engine_),
        Camera(Camera_) {}

  void Render();

 private:
  void RenderTilesAndObjects();
  void RenderActors();
  void RenderRoof();

  const cEngine &Engine;
  cBackground Background;
  const cCamera &Camera;
  cPlanetShaper PlanetShaper;
  const int GroundTypeWaterId = GetId("GroundTypeWater");
  const int GroundTypeWaterAnimatedId[4] = {
    GetId("GroundTypeWater"),
    GetId("GroundTypeWater1"),
    GetId("GroundTypeWater2"),
    GetId("GroundTypeWater3")
  };
};

}  // namespace Forradia
