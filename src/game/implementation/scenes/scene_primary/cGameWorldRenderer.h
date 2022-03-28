// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cEngine.h"
#include "CommonExternal.h"
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
  const cEngine &Engine;
  cBackground Background;
  const cCamera &Camera;
  cPlanetShaper PlanetShaper;
};

}  // namespace Forradia
