// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <algorithm>
#include "cCamera.h"
#include "../engine/cEngine.h"
#include "implementation/functionality/actor/modules/cModuleMovementData.h"

namespace Forradia {

void cCamera::Update(int RotationDirection, float ZoomChange) {
  if (Ticks() > tickLastUpdate + updateSpeed) {
    if (RotationDirection == GetId("Right"))
      lookingAngle -= rotationAmount;
    else if (RotationDirection == GetId("Left"))
      lookingAngle += rotationAmount;

    tickLastUpdate = Ticks();
  }

  zoomAmount += ZoomChange * zoomMultiplier / 100.0f;
  //ZoomAmount = std::min(std::max(ZoomAmount, 0.5f), 15.0f);
  zoomAmount = std::min(std::max(zoomAmount, -3.0f), 15.0f);

  // -----------Ray Casting----------------

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerspective(45, 1.333, 0.5, 100);
  gluPerspective(engine.fov, 1.333, 0.5, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  auto CameraX = 0.0f;
  auto CameraZ = -1.0f;
  auto AngleRadians = atan2(CameraZ, CameraX) + lookingAngle / 180.0f * M_PI;
  auto CameraDist = 1;
  auto Zoom = zoomAmount;

  auto ZoomEx = std::max(Zoom, 1.0f);
  glTranslatef(0.0f, -ZoomEx - 1, - (ZoomEx - 1.0f)* 4.0f);

  CameraX = static_cast<float>(cos(AngleRadians)) * CameraDist;
  CameraZ = -static_cast<float>(sin(AngleRadians)) * CameraDist;

  gluLookAt(CameraX-engine.tileSize/2,
            cameraHeight*(ZoomEx - 0.5f),
            CameraZ-engine.tileSize/2,
            -engine.tileSize/2,
            -1,
            -engine.tileSize/2,
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

  auto MousePosition = utilities.GetMousePositionI();

  GLfloat WinX, WinY, WinZ;  // Holds Our X, Y and Z Coordinates

  WinX = static_cast<float>(MousePosition.x);  // Holds The Mouse X Coordinate
  WinY = static_cast<float>(MousePosition.y);
  WinY = static_cast<float>(Viewport[3]) - WinY;

  glReadPixels((GLint)WinX, (GLint)WinY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT,
               &WinZ);

  GLdouble PosX, PosY, PosZ;

  gluUnProject(WinX, WinY, WinZ, Modelview, Projection, Viewport, &PosX, &PosY,
               &PosZ);

  rayCastingX = static_cast<float>(PosX);
  rayCastingY = static_cast<float>(PosY);
  rayCastingZ = static_cast<float>(PosZ);
}

cPoint2 cCamera::GetHoveredTile() const {
  float SubStepX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x -
          static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.x);

  float SubStepY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y -
          static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.y);

  auto OffsetX = -static_cast<float>(2 * renderDistance + 1)
          / 2.0f * engine.tileSize - SubStepX * engine.tileSize;
  auto OffsetY = -static_cast<float>(2 * renderDistance - 1)
          / 2.0f * engine.tileSize - SubStepY * engine.tileSize;
  auto MapX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x - renderDistance +
              (rayCastingX - OffsetX) / engine.tileSize;
  auto MapY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y - renderDistance +
              (rayCastingZ - OffsetY) / engine.tileSize + 1;

  return {static_cast<int>(MapX), static_cast<int>(MapY)};
}

int cCamera::GetRenderDistance() const {
  auto &MapArea = engine.GetCurrentMapArea();

  if (MapArea.IsUnderground())
    return renderDistanceCave;
  else
    return renderDistance;
}

void cCamera::UpdateCameraMovement() {
  auto MousePosition = utilities.GetMousePositionI();
  auto DeltaMouseX = MousePosition.x - previousMousePosition.x;

  if (engine.mouseHandler.rightButtonDown)
    lookingAngle -= DeltaMouseX / 5.0f;

  auto DeltaMouseY = MousePosition.y - previousMousePosition.y;

  if (engine.mouseHandler.rightButtonDown) {
    cameraHeight += DeltaMouseY / 100.0f;
    cameraHeight = std::max(std::min(cameraHeight, 2.0f), -1.0f);
  }

  previousMousePosition = MousePosition;
}

}  // namespace Forradia
