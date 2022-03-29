// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include "../engine/cUtilities.h"

namespace Forradia {

class cEngine;

class cCamera {
 public:
  explicit cCamera(const cEngine &Engine_) : Engine(Engine_) {}

  void Update(int RotationDirection, float ZoomChange);
  void UpdateCameraMovement();

  float LookingAngle = 0.0f;
  float ZoomAmount = 2.0f;

  float RayCastingX = 0.0f;
  float RayCastingY = 0.0f;
  float RayCastingZ = 0.0f;

  cPoint2 GetHoveredTile() const;
  float CameraHeight = 0.0f;

  int GetRenderDistance() const;

 private:
  const cEngine &Engine;
  cUtilities Utilities;

  cPoint2 PreviousMousePosition = {-1, -1};
  int RenderDistance = 80;
  int RenderDistanceCave = 15;
  unsigned int TickLastUpdate = 0;
  int UpdateSpeed = 20;
  float RotationAmount = 5.0f;
  float ZoomMultiplier = 8.0;
};

}  // namespace Forradia
