// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include "../engine/Utilities.h"

namespace Forradia {

class cEngine;

class cCamera {
 public:
  explicit cCamera(const cEngine &_engine) : engine(_engine) {}

  void Update(int rotationDirection, float zoomChange);
  void UpdateCameraMovement();

  float lookingAngle = 0.0f;
  float zoomAmount = 2.0f;

  float rayCastingX = 0.0f;
  float rayCastingY = 0.0f;
  float rayCastingZ = 0.0f;

  cPoint2 GetHoveredTile() const;
  float cameraHeight = 0.0f;

  int GetRenderDistance() const;

 private:
  const cEngine &engine;
  cUtilities utilities;

  cPoint2 previousMousePosition = {-1, -1};
  int renderDistance = 80;
  int renderDistanceCave = 15;
  unsigned int tickLastUpdate = 0;
  int updateSpeed = 20;
  float rotationAmount = 5.0f;
  float zoomMultiplier = 8.0;
};

}  // namespace Forradia
