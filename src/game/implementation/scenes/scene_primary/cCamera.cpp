// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <algorithm>
#include "cCamera.h"
#include "../engine/cEngine.h"
#include "implementation/functionality/actor/modules/cModuleMovementData.h"

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
  //ZoomAmount = std::min(std::max(ZoomAmount, 0.5f), 15.0f);
  ZoomAmount = std::min(std::max(ZoomAmount, -3.0f), 15.0f);

  // -----------Ray Casting----------------

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerspective(45, 1.333, 0.5, 100);
  gluPerspective(120, 1.333, 0.5, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  auto CameraX = 0.0f;
  auto CameraZ = -1.0f;
  auto AngleRadians = atan2(CameraZ, CameraX) + LookingAngle / 180.0f * M_PI;
  auto CameraDist = 1;
  auto Zoom = ZoomAmount;

  auto ZoomEx = std::max(Zoom, 1.0f);
  glTranslatef(0.0f, -ZoomEx - 1, - (ZoomEx - 1.0f)* 4.0f);

  CameraX = static_cast<float>(cos(AngleRadians)) * CameraDist;
  CameraZ = -static_cast<float>(sin(AngleRadians)) * CameraDist;

  gluLookAt(CameraX-Engine.tileSize/2,
            CameraHeight*(ZoomEx - 0.5f),
            CameraZ-Engine.tileSize/2,
            -Engine.tileSize/2,
            -1,
            -Engine.tileSize/2,
            0,
            1,
            0);

  GLint Viewport[4];  // Where The Viewport Values Will Be Stored

  glGetIntegerv(GL_VIEWPORT, Viewport);

  GLdouble Modelview[16];

  glGetDoublev(GL_MODELVIEW_MATRIX, Modelview);

  GLdouble Projection[16];  // Where The 16 Doubles Of The Projection Matrix Are
                            // To Be Stored

  glGetDoublev(GL_PROJECTION_MATRIX, Projection);

  auto MousePosition = Utilities.GetMousePositionI();

  GLfloat WinX, WinY, WinZ;  // Holds Our X, Y and Z Coordinates

  WinX = static_cast<float>(MousePosition.x);  // Holds The Mouse X Coordinate
  WinY = static_cast<float>(MousePosition.y);
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
  float SubStepX = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x -
          static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x);

  float SubStepY = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y -
          static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y);

  auto OffsetX = -static_cast<float>(2 * RenderDistance + 1)
          / 2.0f * Engine.tileSize - SubStepX * Engine.tileSize;
  auto OffsetY = -static_cast<float>(2 * RenderDistance - 1)
          / 2.0f * Engine.tileSize - SubStepY * Engine.tileSize;
  auto MapX = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x - RenderDistance +
              (RayCastingX - OffsetX) / Engine.tileSize;
  auto MapY = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y - RenderDistance +
              (RayCastingZ - OffsetY) / Engine.tileSize + 1;

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
  auto DeltaMouseX = MousePosition.x - PreviousMousePosition.x;

  if (Engine.mouseHandler.rightButtonDown)
    LookingAngle -= DeltaMouseX / 5.0f;

  auto DeltaMouseY = MousePosition.y - PreviousMousePosition.y;

  if (Engine.mouseHandler.rightButtonDown) {
    CameraHeight += DeltaMouseY / 100.0f;
    CameraHeight = std::max(std::min(CameraHeight, 2.0f), -1.0f);
  }

  PreviousMousePosition = MousePosition;
}

}  // namespace Forradia
