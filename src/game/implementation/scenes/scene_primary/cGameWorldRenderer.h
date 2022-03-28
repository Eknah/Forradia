// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cEngine.h"
#include "CommonExternal.h"
#include "cBackground.h"
#include "cCamera.h"
#include "cPlanetTransformator.h"

namespace Forradia {

class cGameWorldRenderer {
 public:
  cGameWorldRenderer(cEngine &Engine_, cCamera &Camera_)
      : Engine(Engine_), Background(Engine_), PlanetTransformator(Engine_),
        Camera(Camera_) {}

  void Render();

 private:
  cEngine &Engine;
  cBackground Background;
  cCamera &Camera;
  cPlanetTransformator PlanetTransformator;
};

} // namespace Forradia
