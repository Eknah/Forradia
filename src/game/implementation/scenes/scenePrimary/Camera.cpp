// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <algorithm>
#include "Camera.h"
#include "../engine/Engine.h"
#include "implementation/functionality/actor/modules/MovementDataModule.h"

namespace Forradia
{

    void Camera::Update(int rotationDirection, float zoomChange)
    {
        if (Ticks() > tickLastUpdate + updateSpeed)
        {
            if (rotationDirection == GetId("Right"))
                lookingAngle -= rotationAmount;
            else if (rotationDirection == GetId("Left"))
                lookingAngle += rotationAmount;

            tickLastUpdate = Ticks();
        }

        zoomAmount += zoomChange * zoomMultiplier / 100.0f;
        //ZoomAmount = std::min(std::max(ZoomAmount, 0.5f), 15.0f);
        zoomAmount = std::min(std::max(zoomAmount, -3.0f), 15.0f);

        // -----------Ray Casting----------------

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //gluPerspective(45, 1.333, 0.5, 100);
        gluPerspective(e.fov, 1.333, 0.5, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        auto cameraX = 0.0f;
        auto cameraZ = -1.0f;
        auto angleRadians = atan2(cameraZ, cameraX) + lookingAngle / 180.0f * M_PI;
        auto cameraDist = 1;
        auto zoom = zoomAmount;

        auto zoomEx = std::max(zoom, 1.0f);
        glTranslatef(0.0f, -zoomEx - 1, -(zoomEx - 1.0f) * 4.0f);

        cameraX = static_cast<float>(cos(angleRadians)) * cameraDist;
        cameraZ = -static_cast<float>(sin(angleRadians)) * cameraDist;

        gluLookAt(cameraX - e.tileSize / 2,
            cameraHeight * (zoomEx - 0.5f),
            cameraZ - e.tileSize / 2,
            -e.tileSize / 2,
            -1,
            -e.tileSize / 2,
            0,
            1,
            0);

        GLint viewport[4];  // Where The Viewport Values Will Be Stored

        glGetIntegerv(GL_VIEWPORT, viewport);

        GLdouble modelview[16];

        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

        GLdouble projection[16];  // Where The 16 Doubles Of The Projection Matrix Are
                                  // To Be Stored

        glGetDoublev(GL_PROJECTION_MATRIX, projection);

        auto mousePosition = utilities.GetMousePosI();

        GLfloat winX, winY, winZ;  // Holds Our X, Y and Z Coordinates

        winX = static_cast<float>(mousePosition.x);  // Holds The Mouse X Coordinate
        winY = static_cast<float>(mousePosition.y);
        winY = static_cast<float>(viewport[3]) - winY;

        glReadPixels((GLint)winX, (GLint)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT,
            &winZ);

        GLdouble posx, posy, posz;

        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posx, &posy,
            &posz);

        rayCastingX = static_cast<float>(posx);
        rayCastingY = static_cast<float>(posy);
        rayCastingZ = static_cast<float>(posz);
    }

    Point2 Camera::GetHoveredTile() const
    {
        float subStepX = e.GetPlayer().GetModule<MovementDataModule>().position.x -
            static_cast<int>(e.GetPlayer().GetModule<MovementDataModule>().position.x);

        float subStepY = e.GetPlayer().GetModule<MovementDataModule>().position.y -
            static_cast<int>(e.GetPlayer().GetModule<MovementDataModule>().position.y);

        auto offsetX = -static_cast<float>(2 * renderDistance + 1)
            / 2.0f * e.tileSize - subStepX * e.tileSize;
        auto offsetY = -static_cast<float>(2 * renderDistance - 1)
            / 2.0f * e.tileSize - subStepY * e.tileSize;
        auto mapx = e.GetPlayer().GetModule<MovementDataModule>().position.x - renderDistance +
            (rayCastingX - offsetX) / e.tileSize;
        auto mapy = e.GetPlayer().GetModule<MovementDataModule>().position.y - renderDistance +
            (rayCastingZ - offsetY) / e.tileSize + 1;

        return { static_cast<int>(mapx), static_cast<int>(mapy) };
    }

    int Camera::GetRenderDistance() const
    {
        auto& mapArea = e.GetCurrentMapArea();

        if (mapArea.IsUnderground())
            return renderDistanceCave;
        else
            return renderDistance;
    }

    void Camera::UpdateCameraMovement()
    {
        auto mousePosition = utilities.GetMousePosI();
        auto deltaMouseX = mousePosition.x - previousMousePosition.x;

        if (e.mouseHandler.rightButtonDown)
            lookingAngle -= deltaMouseX / 5.0f;

        auto deltaMouseY = mousePosition.y - previousMousePosition.y;

        if (e.mouseHandler.rightButtonDown)
        {
            cameraHeight += deltaMouseY / 100.0f;
            cameraHeight = std::max(std::min(cameraHeight, 2.0f), -1.0f);
        }

        previousMousePosition = mousePosition;
    }

}  // namespace Forradia
