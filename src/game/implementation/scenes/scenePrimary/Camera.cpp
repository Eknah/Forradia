// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <algorithm>
#include "Camera.h"
#include "../engine/Engine.h"
#include "implementation/functionality/actor/modules/CoreMovementModule.h"

namespace Forradia
{
    void Camera::Update()
    {
        SetupCamera();

        GLint viewport[4];
        GLdouble modelview[16];
        GLdouble projection[16];
        GLfloat winX;
        GLfloat winY;
        GLfloat winZ;
        GLdouble posx;
        GLdouble posy;
        GLdouble posz;

        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);

        auto mousePos = utils.GetMousePosI();

        winX = CFloat(mousePos.x);
        winY = CFloat(mousePos.y);
        winY = CFloat(viewport[3]) - winY;

        glReadPixels((GLint)winX, (GLint)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posx, &posy, &posz);

        rayCastingX = CFloat(posx);
        rayCastingY = CFloat(posy);
        rayCastingZ = CFloat(posz);
    }

    void Camera::SetupCamera() const
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(e.cfg.fov, 1.333, 0.5, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        auto cameraX = 0.0f;
        auto cameraZ = -1.0f;
        auto angleRadians = atan2(cameraZ, cameraX) + lookingAngle / 180.0f * M_PI;
        auto cameraDist = 1;
        auto zoom = zoomAmount;

        auto zoomEx = std::max(zoom, 1.0f);
        glTranslatef(0.0f, -zoomEx - 1, -(zoomEx - 1.0f) * 4.0f);

        cameraX = CFloat(cos(angleRadians)) * cameraDist;
        cameraZ = -CFloat(sin(angleRadians)) * cameraDist;

        gluLookAt
        (
            cameraX - e.cfg.tileSize / 2,
            cameraHeight * (zoomEx - 0.5f),
            cameraZ - e.cfg.tileSize / 2,
            -e.cfg.tileSize / 2,
            -1,
            -e.cfg.tileSize / 2,
            0,
            1,
            0
        );
    }

    void Camera::UpdateRotation(int rotationDirection)
    {
        if (timer.HasFinished())
        {
            if (rotationDirection == GetId("Right"))
                lookingAngle -= rotationAmount;
            else if (rotationDirection == GetId("Left"))
                lookingAngle += rotationAmount;

            timer.Reset();
        }
    }

    void Camera::UpdateZoomChange(float zoomChange)
    {
        zoomAmount += zoomChange * zoomMultiplier / 100.0f;
        zoomAmount = std::min(std::max(zoomAmount, -3.0f), 15.0f);
    }

    Point2 Camera::GetHoveredTile() const
    {
        float subStepX = e.GetPlayer().GetModule<CoreMovementModule>().position.x - CInt(e.GetPlayer().GetModule<CoreMovementModule>().position.x);
        float subStepY = e.GetPlayer().GetModule<CoreMovementModule>().position.y - CInt(e.GetPlayer().GetModule<CoreMovementModule>().position.y);

        auto offsetX = -CFloat(2 * renderDistance + 1) / 2.0f * e.cfg.tileSize - subStepX * e.cfg.tileSize;
        auto offsetY = -CFloat(2 * renderDistance - 1) / 2.0f * e.cfg.tileSize - subStepY * e.cfg.tileSize;
        auto mapx = e.GetPlayer().GetModule<CoreMovementModule>().position.x - renderDistance + (rayCastingX - offsetX) / e.cfg.tileSize;
        auto mapy = e.GetPlayer().GetModule<CoreMovementModule>().position.y - renderDistance + (rayCastingZ - offsetY) / e.cfg.tileSize + 1;

        return { CInt(mapx), CInt(mapy) };
    }

    int Camera::GetRenderDist() const
    {
        auto& mapArea = e.GetCurrMapArea();

        if (mapArea.IsUnderground())
            return renderDistanceCave;
        else
            return renderDistance;
    }

    void Camera::UpdateCameraMovm()
    {
        auto mousePos = utils.GetMousePosI();
        auto deltaMouseX = mousePos.x - previousMousePos.x;
        auto deltaMouseY = mousePos.y - previousMousePos.y;

        if (e.mouseHandler.rightButtonDown)
            lookingAngle -= deltaMouseX / 5.0f;

        if (e.mouseHandler.rightButtonDown)
        {
            cameraHeight += deltaMouseY / 100.0f;
            cameraHeight = std::max(std::min(cameraHeight, 2.0f), -1.0f);
        }

        previousMousePos = mousePos;
    }

}  // namespace Forradia
