// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cCamera.h"
#include "../engine/cEngine.h"

namespace Forradia
{

void cCamera::Update(int RotationDirection, float ZoomChange)
{
    if (Ticks() > TickLastUpdate + UpdateSpeed)
    {
        if (RotationDirection == GetId("Right"))
            LookingAngle -= RotationAmount;
        else if (RotationDirection == GetId("Left"))
            LookingAngle += RotationAmount;

        TickLastUpdate = Ticks();
    }

    ZoomAmount += ZoomChange * ZoomMultiplier / 100.0f;
    ZoomAmount = std::min(std::max(ZoomAmount, 0.5f), 15.0f);

    //-----------Ray Casting----------------

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

    CameraX = (float)cos(AngleRadians) * CameraDist;
    CameraZ = -(float)sin(AngleRadians) * CameraDist;

    gluLookAt(CameraX, CameraHeight, CameraZ, 0, -1, 0, 0, 1, 0);

    GLint Viewport[4];                  // Where The Viewport Values Will Be Stored

    glGetIntegerv(GL_VIEWPORT, Viewport);

    GLdouble Modelview[16];

    glGetDoublev(GL_MODELVIEW_MATRIX, Modelview);

    GLdouble Projection[16];                // Where The 16 Doubles Of The Projection Matrix Are To Be Stored

    glGetDoublev(GL_PROJECTION_MATRIX, Projection);

    auto MousePosition = Utilities.GetMousePositionI();

    GLfloat WinX, WinY, WinZ;               // Holds Our X, Y and Z Coordinates

    WinX = (float)MousePosition.X;                  // Holds The Mouse X Coordinate
    WinY = (float)MousePosition.Y;
    WinY = (float)Viewport[3] - WinY;

    glReadPixels((GLint)WinX, (GLint)WinY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &WinZ);

    GLdouble PosX, PosY, PosZ;

    gluUnProject(WinX, WinY, WinZ, Modelview, Projection, Viewport, &PosX, &PosY, &PosZ);

    RayCastingX = (float)PosX;
    RayCastingY = (float)PosY;
    RayCastingZ = (float)PosZ;
}

cPoint2 cCamera::GetHoveredTile()
{
    float SubStepX = Engine.Player.Position.X - (int)Engine.Player.Position.X;
    float SubStepY = Engine.Player.Position.Y - (int)Engine.Player.Position.Y;

    auto OffsetX = -(double)(2 * RenderDistance + 1) / 2.0 * Engine.TileSize - SubStepX * Engine.TileSize;
    auto OffsetY = -(double)(2 * RenderDistance - 1) / 2.0 * Engine.TileSize - SubStepY * Engine.TileSize;
    auto MapX = Engine.Player.Position.X - RenderDistance + (RayCastingX - OffsetX) / Engine.TileSize;
    auto MapY = Engine.Player.Position.Y - RenderDistance + (RayCastingZ - OffsetY) / Engine.TileSize + 1;

    return { (int)MapX, (int)MapY };
}

int cCamera::GetRenderDistance()
{
    auto& MapArea = Engine.GetCurrentMapArea();

    if (MapArea.IsUnderground())
        return RenderDistanceCave;
    else
        return RenderDistance;
}

void cCamera::UpdateCameraMovement()
{
    auto MousePosition = Utilities.GetMousePositionI();
    auto DeltaMouseX = MousePosition.X - PreviousMousePosition.X;

    if (Engine.MouseHandler.RightButtonDown)
        LookingAngle -= DeltaMouseX / 5.0f;

    auto DeltaMouseY = MousePosition.Y - PreviousMousePosition.Y;

    if (Engine.MouseHandler.RightButtonDown)
    {
        CameraHeight += DeltaMouseY / 100.0f;
        CameraHeight = std::max(std::min(CameraHeight, 2.0f), -1.0f);
    }

    PreviousMousePosition = MousePosition;
}

}
