// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <algorithm>
#include "cCamera.h"
#include "../engine/cEngine.h"

namespace Forradia {

void cCamera::Update(int RotationDirection, float ZoomChange) {
  if (Ticks() > TickLastUpdate + UpdateSpeed) {
    if (RotationDirection == GetId("Right"))
      LookingAngle -= RotationAmount;
    else if (RotationDirection == GetId("Left"))
      LookingAngle += RotationAmount;

    TickLastUpdate = Ticks();
  }

  ZoomAmount += ZoomChange * ZoomMultiplier / 100.0f;
  ZoomAmount = std::min(std::max(ZoomAmount, 0.5f), 15.0f);

  // -----------Ray Casting----------------

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, 1.333, 0.5, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  auto CameraX = 0.0f;
  auto CameraZ = -1.0f;
  auto AngleRadians = atan2(CameraZ, CameraX) + LookingAngle / 180.0f * M_PI;
  auto CameraDist = 1;
  auto Zoom = ZoomAmount;

  glTranslatef(0.0f, -Zoom, -2.0f - Zoom * 4.0f);

  CameraX = static_cast<float>(cos(AngleRadians)) * CameraDist;
  CameraZ = -static_cast<float>(sin(AngleRadians)) * CameraDist;

  gluLookAt(CameraX, CameraHeight, CameraZ, -Engine.TileSize/2, -1, -Engine.TileSize/2, 0, 1, 0);

  GLint Viewport[4];  // Where The Viewport Values Will Be Stored

  glGetIntegerv(GL_VIEWPORT, Viewport);

  GLdouble Modelview[16];

  glGetDoublev(GL_MODELVIEW_MATRIX, Modelview);

  GLdouble Projection[16];  // Where The 16 Doubles Of The Projection Matrix Are
                            // To Be Stored

  glGetDoublev(GL_PROJECTION_MATRIX, Projection);

  auto MousePosition = Utilities.GetMousePositionI();

  GLfloat WinX, WinY, WinZ;  // Holds Our X, Y and Z Coordinates

  WinX = static_cast<float>(MousePosition.X);  // Holds The Mouse X Coordinate
  WinY = static_cast<float>(MousePosition.Y);
  WinY = static_cast<float>(Viewport[3]) - WinY;

  glReadPixels((GLint)WinX, (GLint)WinY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT,
               &WinZ);

  GLdouble PosX, PosY, PosZ;

  gluUnProject(WinX, WinY, WinZ, Modelview, Projection, Viewport, &PosX, &PosY,
               &PosZ);

  RayCastingX = static_cast<float>(PosX);
  RayCastingY = static_cast<float>(PosY);
  RayCastingZ = static_cast<float>(PosZ);
}

cPoint2 cCamera::GetHoveredTile() const {
  float SubStepX = Engine.GetPlayer().Position.X -
          static_cast<int>(Engine.GetPlayer().Position.X);

  float SubStepY = Engine.GetPlayer().Position.Y -
          static_cast<int>(Engine.GetPlayer().Position.Y);

  auto OffsetX = -static_cast<float>(2 * RenderDistance + 1)
          / 2.0f * Engine.TileSize - SubStepX * Engine.TileSize;
  auto OffsetY = -static_cast<float>(2 * RenderDistance - 1)
          / 2.0f * Engine.TileSize - SubStepY * Engine.TileSize;
  auto MapX = Engine.GetPlayer().Position.X - RenderDistance +
              (RayCastingX - OffsetX) / Engine.TileSize;
  auto MapY = Engine.GetPlayer().Position.Y - RenderDistance +
              (RayCastingZ - OffsetY) / Engine.TileSize + 1;

  return {static_cast<int>(MapX), static_cast<int>(MapY)};
}

int cCamera::GetRenderDistance() const {
  auto &MapArea = Engine.GetCurrentMapArea();

  if (MapArea.IsUnderground())
    return RenderDistanceCave;
  else
    return RenderDistance;
}

void cCamera::UpdateCameraMovement() {
  auto MousePosition = Utilities.GetMousePositionI();
  auto DeltaMouseX = MousePosition.X - PreviousMousePosition.X;

  if (Engine.MouseHandler.RightButtonDown)
    LookingAngle -= DeltaMouseX / 5.0f;

  auto DeltaMouseY = MousePosition.Y - PreviousMousePosition.Y;

  if (Engine.MouseHandler.RightButtonDown) {
    CameraHeight += DeltaMouseY / 100.0f;
    CameraHeight = std::max(std::min(CameraHeight, 2.0f), -1.0f);
  }

  PreviousMousePosition = MousePosition;
}

}  // namespace Forradia
